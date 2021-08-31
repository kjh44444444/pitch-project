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
#define STASSID "WAVLINK-N"
#define STAPSK  "Purdue.edu1"
#define deskID  "1"

#endif

// ê³µìœ ê¸° Info
const char* ssid = STASSID;
const char* password = STAPSK;

// Ultrasonic Pinì§€ì 
int trig = 4;
int echo = 5;

WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
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
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {return;}
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){delay(1);}
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Ultrasonic distancing
  digitalWrite(trig,LOW);
  digitalWrite(echo,LOW);
  delayMicroseconds(2);
  
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  float distance = pulseIn(echo, HIGH) * 17/1000;

  Serial.print(distance);
  Serial.println("cm");
  delay(100);

  //
  delay(2000);

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println("Refresh: 1");  
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.print("Distance is ");
  client.println(distance);
  client.println("cm");
  String a = "<meta http-equiv= \"refresh\" content=\"1;url=http://localhost/process.php?deskID=";
  client.println("<script> window.open('${a} + ${deskID} + \"&distance=\"+${distance}+"">");
  client.println("</script>");
  //client.println(a + deskID + "&distance="+distance+"\">");
  //Serial.println(a + deskID + "&distance="+distance+"\">");
  Serial.println("uploaded");
  client.println("</html>"); 
  Serial.println();
  Serial.println("closing connection");
  
}
