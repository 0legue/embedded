#include "main.h"

WebServer server(80);

const char* ssid = "dyrdom";
const char* password = "0990371234";

char htmlResponse[3000];
int ir = 13;
int led = 14;

void handleRoot() 
{
  snprintf ( htmlResponse, 3000,
  "<!DOCTYPE html>\
  <html lang=\"en\">\
    <head>\
      <meta charset=\"utf-8\">\
      <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
    </head>\
    <body>\
      <h1>LED</h1>\
      <div>\
      <button id=\"led_button_on\">Turn on LED</button><button id=\"led_button_off\">Turn off LED</button>\
      </div>\  
      <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script>\    
      <script>\
        $('#led_button_off').click(function(e){\
          e.preventDefault();\
          var led=1;\
          $.get('/save?led=' + led, function(data){\
            console.log(data);\
          });\
        });\   
        $('#led_button_on').click(function(e){\
          e.preventDefault();\
          var led=2;\
          $.get('/save?led=' + led, function(data){\
            console.log(data);\
          });\
        });\  
      </script>\
    </body>\
  </html>"); 
  server.send ( 200, "text/html", htmlResponse );  
  Serial.println("HANDLING ROOT");
}

void handleSave() 
{
  //Serial.println(server.args());
  if (server.args()==1){
    if (server.arg("led").toInt()==1){
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("Changing LED state to OFF");
    }
    else{
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("Changing LED state to ON");
    }  
  }  
}

void setup() 
{
 pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.on ( "/", handleRoot );
  server.on ("/save", handleSave);
  server.begin();
  Serial.println ( "HTTP server started" );


  pinMode(ir, INPUT);
          pinMode(led, OUTPUT);
          Serial.begin(115200);
}

void loop()
{
  server.handleClient();

  int irvalue=digitalRead(ir);
      if(irvalue==LOW)
      {
      Serial.println("LOW");
            digitalWrite(led,HIGH);
      }
      else
      {
        Serial.println("High");
            digitalWrite(led,LOW);
      }
      delay(100);
}
