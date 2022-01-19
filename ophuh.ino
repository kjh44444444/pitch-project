/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>

#ifndef STASSID
//#define STASSID "WAVLINK-N"
#define STASSID "jhkim"
#define STAPSK  "00000000"
#define deskID  "1"

#endif

// ê³µìœ ê¸° Info
const char* ssid = STASSID;
const char* password = STAPSK;

// Ultrasonic Pinì§€ì 
int trig = 4;
int echo = 5;
int pirsen = D7;

int    HTTP_PORT   = 80;
String HTTP_METHOD = "POST"; // or "POST"
//char   HOST_NAME[] = "http://72.12.223.185"; // hostname of web server:
char   HOST_NAME[] = "localhost"; // hostname of web server:
String PATH_NAME   = "/process.php";

WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  pinMode(pirsen, INPUT);//pir
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  delay(10);
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

  WiFiClient client;
  // Ultrasonic distancing
  digitalWrite(trig,LOW);
  digitalWrite(echo,LOW);
  delayMicroseconds(2);
  
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  float distance = pulseIn(echo, HIGH) * 17/1000;
  int seated = 0;
  int sc =0;
  int nsc =0;
  long state = digitalRead(pirsen);
  
  Serial.print("pir sensor: ");  
  
  Serial.println(state);  
    
    if (state==HIGH|distance <= 18){
      seated = 1;
     // sc +=1;
      Serial.println("Seated and pir sensor detected the motion");
      if(distance <= 18){
        Serial.println("distance satisfied");
//        int sc =0;
          nsc += 1;
      }
      if(state==HIGH){
        Serial.println("motion detected");
      }
      //state =0;
    }

    while(nsc >= 360){
      long state = digitalRead(pirsen);
      if(state == HIGH){
        nsc == 0;
      }
    }
  //if(sc ==10){
  //  sc =0;
   // state=0;
 // }

  //Serial.print(distance);


  Serial.print("distance: ");
  Serial.println(distance);
  
//  Serial.println("cm");

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
