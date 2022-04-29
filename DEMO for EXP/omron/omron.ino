#include <ESP8266WiFi.h>

#ifndef STASSID
//#define STASSID "WAVLINK-N"
#define STASSID "10101010"
#define STAPSK  "00000000"
#define deskID  "12"

#endif

// ê³µìœ ê¸° Info
const char* ssid = STASSID;
const char* password = STAPSK;

// Ultrasonic Pinì§€ì 
int trig = 4;
int echo = 5;
int pirsen = D7;

int    HTTP_PORT   = 80;
String HTTP_METHOD = "POST"; // or "POST"
char   HOST_NAME[] = "http://72.12.223.185"; // hostname of web server:
//char   HOST_NAME[] = "localhost"; // hostname of web server:
String PATH_NAME   = "/process.php";

WiFiServer server(80);

//omron 
#include <Wire.h>

/* defines */
#define D6T_ADDR 0x0A  // for I2C 7bit address
#define D6T_CMD 0x4C  // for D6T-44L-06/06H, D6T-8L-09/09H, for D6T-1A-01/02

#define N_ROW 1
#define N_PIXEL 1
#define N_READ ((N_PIXEL + 1) * 2 + 1)

uint8_t rbuf[N_READ];
double ptat;
double pix_data[N_PIXEL];

uint8_t calc_crc(uint8_t data) {
    int index;
    uint8_t temp;
    for (index = 0; index < 8; index++) {
        temp = data;
        data <<= 1;
        if (temp & 0x80) {data ^= 0x07;}
    }
    return data;
}

/** <!-- D6T_checkPEC {{{ 1--> D6T PEC(Packet Error Check) calculation.
 * calculate the data sequence,
 * from an I2C Read client address (8bit) to thermal data end.
 */
bool D6T_checkPEC(uint8_t buf[], int n) {
    int i;
    uint8_t crc = calc_crc((D6T_ADDR << 1) | 1);  // I2C Read address (8bit)
    for (i = 0; i < n; i++) {
        crc = calc_crc(buf[i] ^ crc);
    }
    bool ret = crc != buf[n];
    if (ret) {
        Serial.print("PEC check failed:");
        Serial.print(crc, HEX);
        Serial.print("(cal) vs ");
        Serial.print(buf[n], HEX);
        Serial.println("(get)");
    }
    return ret;
}

/** <!-- conv8us_s16_le {{{1 --> convert a 16bit data from the byte stream.
 */
int16_t conv8us_s16_le(uint8_t* buf, int n) {
    uint16_t ret;
    ret = (uint16_t)buf[n];
    ret += ((uint16_t)buf[n + 1]) << 8;
    return (int16_t)ret;   // and convert negative.
}

/** <!-- setup {{{1 -->
 * 1. Initialize 
       - initialize a Serial port for output.
     - initialize I2C.
 */


//omron

  
  float data[10];
  int n = 0;
  float dataavg = 0;
void setup() {
 
  Serial.begin(115200);
  Wire.begin();  // i2c master
  Serial.println();
 
  // We start by connecting to a WiFi network
  Serial.print("\nConnecting to WiFi");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");    
    }
 
  Serial.println("\nWiFi connected");  
  
  // ì„œë²„ì—°ê²°
  server.begin();
  Serial.println("Server started");

  // Print IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  int seated = 0;
  int i = 0;
  int16_t itemp = 0;
  WiFiClient client;

  
  // Read data via I2C
  // I2C buffer of "Arduino MKR" is 256 buffer. (It is enough)
    memset(rbuf, 0, N_READ);
    Wire.beginTransmission(D6T_ADDR);  // I2C slave address
    Wire.write(D6T_CMD);               // D6T register
    Wire.endTransmission();            
    Wire.requestFrom(D6T_ADDR, N_READ);
    while (Wire.available()) {
        rbuf[i++] = Wire.read();
    }
    D6T_checkPEC(rbuf, N_READ - 1);

    //Convert to temperature data (degC)
    ptat = (double)conv8us_s16_le(rbuf, 0) / 10.0;
  for (i = 0; i < N_PIXEL; i++) {
    itemp = conv8us_s16_le(rbuf, 2 + 2*i);
    pix_data[i] = (double)itemp / 10.0;
  }
    
    //Output results
  Serial.print("PTAT:");
    Serial.print(ptat, 1);
    Serial.print(" [degC], Temperature: ");
  for (i = 0; i < N_PIXEL; i++) {
      Serial.print(pix_data[i], 1);
    Serial.print(", ");
  } 
    Serial.println(" [degC]");

  
  if(pix_data[0]>23.5){
    seated = 1;
  }


  //String queryString = String("?deskID=") + String(deskID) + String("&distance=") + String(distance);
  String queryString = String("?deskID=") + String(deskID) + String("&distance=") + String(seated);
  Serial.println(queryString);

  delay(500);

byte server[] = { 72, 12, 223, 185 };
 if (client.connect(server, 80)) {
    Serial.println("connected");
    client.println("GET /process.php" + queryString + " HTTP/1.0");
    client.println();
  } else {
    Serial.println("connection failed");
  }
}  
