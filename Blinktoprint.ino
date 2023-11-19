


#include <SPI.h>  
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>
char ssid[] = "xxxxx";        // your network SSID (name)
char pass[] = "xxxxx";        // your network password 
char auth[] = "4db61b17050a48cabd55bb114a1f6405"; 
int status = WL_IDLE_STATUS; 
const char* host = "maker.ifttt.com"; 
const int httpsPort = 443; 
void setup() {
  //Initialize serial and wait for port to open
  // sets data rate to 9600 bits per second
  Serial.begin(9600);  
  while (!Serial) {
   ; // wait for serial port to connect. 
 }
     // attempt to connect to Wifi network:
   while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  // you're connected now, so print out the data:
  Serial.print("You're connected to the network");
  // connect to Blynk App via Wifi:
  Blynk.begin(auth, ssid, pass);  
}







void loop() {
int sensor = analogRead(A1);
// This is a major overflow, which needs immediate attention
if (sensor >= 550){send_text_message("high");}
// This is a minor leak, which needs to be fixed soon!
else if (sensor >= 100 && sensor < 550)
{ send_text_message("medium");}
else { // This is not a leak or overflow.}
Blynk.run();  
} 
void send_text_message(char * intensity)
{  
  WiFiClient client;
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connectSSL(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }
  String url = "/trigger/AquaSaver/with/key/j3Cu4Tq4FKz-Q7PvqTbC4";
  // ardiuno board sending trigger for leak-overflow to maker.ifftt.com
  client.print(String("GET ") + url + intensity + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");
  Serial.println("request sent");
}
