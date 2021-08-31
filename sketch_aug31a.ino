 
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2,3);
#define deskID 1;
float dis; //Stores temperature value
int trig = 4;
int echo = 5;
String ssid = "WAVLINK-N"; 
String PASSWORD = "Purdue.edu1"; 
String host = "localhost";

void connectWifi(){ 
  String join ="AT+CWJAP=\""+ssid+"\",\""+PASSWORD+"\""; 
  Serial.println("Connect Wifi..."); 
  mySerial.println(join); delay(10000); 
  if(mySerial.find("OK")) { 
    Serial.print("WIFI connect\n"); 
    }else 
    { 
      Serial.println("connect timeout\n"); 
      } 
      delay(1000);
}

void setup() { 
  Serial.begin(9600); 
  mySerial.begin(9600); 
  connectWifi(); 
  delay(500); 
  }

void loop() { 
  digitalWrite(trig,LOW);
  digitalWrite(echo,LOW);
  delayMicroseconds(2);
  
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW); 
   float distance = pulseIn(echo, HIGH) * 17/1000;

  String str_output = "deskID="+deskID+"&dis="+String(distance); 
  delay(1000); 
  httpclient(str_output); 
  delay(1000); 
  //Serial.find("+IPD"); 
  while (mySerial.available()) {
    char response = mySerial.read(); 
    Serial.write(response); 
    if(response=='\r') 
    Serial.print('\n'); 
    } 
    Serial.println("\n==================================\n"); 
    delay(2000); 
    }

void httpclient(String char_input){ 
  delay(100); 
  Serial.println("connect TCP..."); 
  mySerial.println("AT+CIPSTART=\"TCP\",\""+host+"\",80"); 
  delay(500); 
  if(Serial.find("ERROR")) return;
  Serial.println("Send data...");
  String url=char_input; 
  String cmd="GET /process.php?"+url+" HTTP/1.0\r\n\r\n"; 
  mySerial.print("AT+CIPSEND="); 
  mySerial.println(cmd.length()); 
  Serial.print("AT+CIPSEND="); 
  Serial.println(cmd.length());
  if(mySerial.find(">")) {
    Serial.print(">"); 
    }else {
      mySerial.println("AT+CIPCLOSE"); 
      Serial.println("connect timeout"); 
      delay(1000); 
      return; 
      }
      delay(500);
  mySerial.println(cmd);
  Serial.println(cmd); 
  delay(100); 
  if(Serial.find("ERROR")) return; 
  mySerial.println("AT+CIPCLOSE"); 
  delay(100); 
  }
