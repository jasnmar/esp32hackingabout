/*
 *  This sketch sends a message to a TCP server
 *
 */

#include <WiFi.h>

const char* ssid     = "Meltwater Wireless";
const char* password = "MoroEnereResp";
char newline = '\n';


//#include <WiFiMulti.h>

//WiFiMulti WiFiMulti;
WiFiClient client;

const uint16_t port = 8080;
const char * host = "10.4.8.56"; // ip or dns


void setup()
{
    Serial.begin(115200);
    delay(10);


    // Kill any existing wifi connection
    Serial.println();
    Serial.println();
    Serial.println("Disconnecting Wifi");
    WiFi.disconnect(true);
    delay(1000);
    
    
    // We start by connecting to a WiFi network
    
    WiFi.begin(ssid, password);
    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi... ");



    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(500);
    Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections

    WiFiConnect();

}


bool WiFiConnect(){
      if (!client.connect(host, port)) {
        
        Serial.println("connection failed");
        Serial.println("wait 5 sec...");
        delay(5000);
        if(!client.connected()) {
          return false;
        } else {
          return true;
        }
    }
    
}
void WiFiEvent(WiFiEvent_t event)
{
    Serial.printf("[WiFi-event] event: %d\n", event);

    switch(event) {
    case SYSTEM_EVENT_STA_GOT_IP:
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        Serial.println("WiFi lost connection");
        break;
    }
}
void loop()
{

  if(!client.connected()) {
    WiFiConnect();
  }


 

    // This will send the request to the server
    //client.print("GET / HTTP/1.1");

    client.setTimeout(1000);

    
    //read back one line from server
    while(client.connected()) {
        Serial.println("Client Connected");


        Serial.println("Performing GET");
        
        client.println("GET / HTTP/1.0");
        client.println();
        while (client.peek()!= '\r') {
          String line = client.readStringUntil(newline);
          Serial.print("Data from client is: ");
          Serial.print(line);
          Serial.println();
          
        }

  

    }
    

    //Serial.println("closing connection");
    //client.stop();

    //Serial.println("wait 5 sec...");
    //delay(5000);
}

