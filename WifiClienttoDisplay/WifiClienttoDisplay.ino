


#include <WiFi.h>
//#include <String>

//Wifi Settings
const char* ssid     = "Meltwater Wireless";
const char* password = "MoroEnereResp";

//Server Settings
const uint16_t port = 8080;
const char * host = "10.4.8.87"; // ip or dns
WiFiClient client;

//Display Settings
#include "SSD1306.h"
SSD1306  display(0x3c, 4, 15);



//This is just going to set the top line of the display at this time
void setScreenText(String textToDisplay) {
    // Font Demo1
    // create more fonts at http://oleddisplay.squix.ch/

    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);
//    display.drawString(0, 0, textToDisplay);
    uint16_t maxStringWidth = getStringWidth(textToDisplay)
    display.drawStringMaxWidth(0, 0, maxStringWidth, textToDisplay);
}

void WiFiConnectionError(){
    Serial.println("connection failed");
    Serial.println("wait 5 sec...");
    display.clear();
    setScreenText("Error Connecting to Server");
    display.display();
    delay(5000);
}

bool WiFiConnect(){
  if (!client.connect(host, port)) {
  }
  if(!client.connected()) {
    WiFiConnectionError();
    return false;
  } else {
    return true;
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
void screenSetup() {
  Serial.println("Setting up the Screen");

  pinMode(16,OUTPUT);
  digitalWrite(16, LOW);    // set GPIO16 low to reset OLED
  delay(50); 
  digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 in high

  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

}


String parseResponse(String response) {
  char str[response.length()];
  //const char nl = char('\r');
  response.toCharArray(str,response.length());
  Serial.print("Size of String is: ");
  int strLength = sizeof(str);
  Serial.println(strLength);
  int lineCount = 0;
  String myText;
  for (int i=0; i<strLength; i++){
    //Serial.print(str[i]);
    if(str[i]==char('\n')){
      //Serial.println("Hard Return");
      lineCount++;
    }
    if (lineCount==7){
       myText = myText + str[i]; 

    }

  }
       //Serial.println("Data recieved from Server:");
       Serial.println(myText);
       //Serial.println("That was my text!!!!!!");
       return myText;
  
}

void setup()
{
  //Initialize the serial port (for debugging)
  Serial.begin(115200);
  delay(10);

  // Kill any existing wifi connection
  Serial.println("Disconnecting Wifi");
  WiFi.disconnect(true);
  screenSetup();
  // Clear the screen
  display.clear();
  //post a start up message
  setScreenText("Initializing...");
  display.display();
  
  //give stuff some time to init
  delay(1000);
  
  
  // We start by connecting to a WiFi network
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  //delay(500);
  Serial.print("connecting to ");
  Serial.println(host);

  bool wifiConnected = false;

  while(!!wifiConnected){
    wifiConnected = WiFiConnect();
    if(!wifiConnected) {
      WiFiConnectionError();
    }
  }
}

void loop()
{
  String displayString;

  if(!client.connected()) {
    WiFiConnect();
  }

    //Set the Wificlient timeout
    client.setTimeout(1000);
    
    Serial.println("Attempting Connection");
    
    while(client.connected()) {

        client.println("GET / HTTP/1.0");
        client.println();
        
        String line = client.readString();
        displayString = parseResponse(line);
  

    }
    if (displayString) {
      display.clear();
      setScreenText(displayString);
      display.display();
    }
    
    Serial.println();
    Serial.println("closing connection");
    Serial.println();
    //client.stop();

    //Serial.println("wait 5 sec...");
    //Slowing stuff down for debugging purposes...
    delay(5000);
}

