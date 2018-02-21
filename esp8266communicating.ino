#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "hotspot";
const char* password = "naman1234";
const char* mqttServer = "m14.cloudmqtt.com";
const int mqttPort = 18342;
const char* mqttUser = "tlbfrcmg";
const char* mqttPassword = "WgQ7od5g0OwI";

String read = "";
 
//int ledPin = 13; // GPIO13
WiFiClient espClient;
PubSubClient client(espClient);


int pin1 = 14; // GPIO 14 (D5)
int pin2 = 12; // GPIO 12 (D6)


void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(pin1, OUTPUT); //pin1 output
  pinMode(pin2, OUTPUT); //pin2 output
 

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }

  client.publish("esp/test", "Hello from ESP8266");
  client.subscribe("esp/test");

}

void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    read+=(char)payload[i];
  }

  if(read == "led1on") {
    digitalWrite(pin1, HIGH);
    Serial.println("led1 on");
  }
   if(read == "led2on") {
    digitalWrite(pin2, HIGH);
    Serial.println("led2 on");
  }
   if(read == "led1off") {
    digitalWrite(pin1, LOW);
    Serial.println("led1 off");
  }
   if(read == "led2off") {
    digitalWrite(pin2, LOW);
    Serial.println("led2 off");
  }
 
  Serial.println();
  Serial.println("-----------------------");
  read="";
}

void loop() {
  client.loop();
}

/*void loop() {
  
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Yes client");

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();


        if (readStrings.length() < 100) {
          readStrings += c;
        }

        if (c == '\n') {
          Serial.println(readStrings);
          client.print("HTTP/1.1 200 OK\r\n"); //send new page
          client.print("Content-Type: text/html\r\n\r\n");
          client.print("<!DOCTYPE HTML>\r\n");
          client.print("<HTML>\r\n");//html tag
          client.print("<HEAD>\r\n"); //
          //            client.print("<meta http-equiv='refresh' content='10'/>\r\n");
          client.print("<meta name='apple-mobile-web-app-capable' content='yes' />\r\n");
          client.print("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />\r\n");
          client.print("<link rel='stylesheet' type='text/css' href='http://slumberjer.com/hanis.css' />\r\n");
          client.print("<TITLE>Home Automation</TITLE>\r\n");
          client.print("</HEAD>\r\n");
          client.print("<BODY>\r\n");
          client.print("<H1>My Smart Home System</H1>\r\n");
          client.print("<hr />\r\n");
          client.print("<br />\r\n");
          client.print("<H2>Build Using Nodemcuv1 Arduino</H2>\r\n");
          client.print("<br />\r\n");
          client.print("<p><b>Front Gate</b></p><br />\r\n");
          client.print("<a href=\"/?button1on\"><font color = \"green\">ON   </font></a>\r\n");
          client.print("<a href=\"/?button1off\"><font color = \"red\">OFF  </font></a><br />\r\n");
          client.print("<p><b>Living Room</b></p>");
          client.print("<br />\r\n");
          client.print("<a href=\"/?button2on\"><font color = \"green\">ON   </font></a>\r\n");
          client.print("<a href=\"/?button2off\"><font color = \"red\">OFF  </font></a><br />\r\n");
          client.print("<p><b>Room A</b></p>");
          client.print("<br />\r\n");
          client.print("<a href=\"/?button3on\"><font color = \"green\">ON   </font></a>\r\n");
          client.print("<a href=\"/?button3off\"><font color = \"red\">OFF  </font></a><br />\r\n");
          client.print("<p><b>Room B</b></p>");
          client.print("<br />\r\n");
          client.print("<a href=\"/?button4on\"><font color = \"green\">ON   </font></a>\r\n");
          client.print("<a href=\"/?button4off\"><font color = \"red\">OFF  </font></a><br />\r\n");
          client.print("<br />\r\n");
          client.print("<p><b>All Switches</b></p>");
          client.print("<br />\r\n");
          client.print("<br />\r\n");
          client.print("<a href=\"/?buttonallon\"><font color = \"green\">ALL ON   </font></a>\r\n");
          client.print("<a href=\"/?buttonalloff\"><font color = \"red\">ALL OFF  </font></a><br />\r\n");
          client.print("<br />\r\n");
          client.print("</BODY>\r\n");
          client.print("</HTML>\n");

          delay(1);

          client.stop();
          if (readStrings.indexOf("?button1on") > 0) {
            Serial.println("1 on");
            digitalWrite(pin1, LOW);
          }
          if (readStrings.indexOf("?button1off") > 0) {
            Serial.println("1 off");
            digitalWrite(pin1, HIGH);
          }

          if (readStrings.indexOf("?button2on") > 0) {
            Serial.println("2 on");
            digitalWrite(pin2, LOW);
          }
          if (readStrings.indexOf("?button2off") > 0) {
            Serial.println("2 off");
            digitalWrite(pin2, HIGH);
          }
          if (readStrings.indexOf("?button3on") > 0) {
            digitalWrite(pin3, LOW);
            Serial.println("3 on");
          }
          if (readStrings.indexOf("?button3off") > 0) {
            digitalWrite(pin3, HIGH);
            Serial.println("3 off");
          }
          if (readStrings.indexOf("?button4on") > 0) {
            digitalWrite(pin4, LOW);
            Serial.println("4 on");
          }
          if (readStrings.indexOf("?button4off") > 0) {
            digitalWrite(pin4, HIGH);
            Serial.println("4 off");
          }
          if (readStrings.indexOf("?buttonallon") > 0) {
            digitalWrite(pin1, LOW);
            digitalWrite(pin2, LOW);
            digitalWrite(pin3, LOW);
            digitalWrite(pin4, LOW);
          }
          if (readStrings.indexOf("?buttonalloff") > 0) {
            digitalWrite(pin1, HIGH);
            digitalWrite(pin2, HIGH);
            digitalWrite(pin3, HIGH);
            digitalWrite(pin4, HIGH);
          }
          readStrings = "";
        }
      }
    }
  }
}*/

