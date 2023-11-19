#define BLYNK_PRINT Serial
#include <SPI.h>  
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>

char ssid[] = "xxxxx";        // your network SSID (name)
char pass[] = "xxxxx";        // your network password 
char auth[] = "4db61b17050a48cabd55bb114a1f6405";
int status = WL_IDLE_STATUS;  // the Wifi status   
const char* host = "maker.ifttt.com"; 
const int httpsPort = 443; 
void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);              // opens serial port, sets data rate to 9600 bits per second
  Blynk.begin(auth, ssid, pass);  // connect to Blynk App via Wifi
  while (!Serial) {
    ; // wait for serial port to connect. 
  }
     // attempt to connect to Wifi network:
   while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    //  Serial.println(ssid);
    // Connect to Wifi Protected Access network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  // you're connected now, so print out the data:
  Serial.print("You're connected to the network");
}

void loop() {
 int sensor=analogRead(A1);
  Blynk.run();  
 if (sensor > 420)
{send_text_message();}
}
void send_text_message()
{  
  WiFiClient client;
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connectSSL(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }
   String url = "/trigger/AquaSaver/with/key/j3Cu4Tq4FKz-Q7PvqTbC4H3IztIgUKFC36jexnu2XG";
  Serial.print("requesting URL: ");
  Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");
  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  Serial.println(line);
  Serial.println("closing connection");
  delay(10000);
}

