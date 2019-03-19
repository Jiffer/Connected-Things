#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// WiFi Parameters
const char* ssid = "btuGoo";
const char* password = "blowItUp";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
}

void loop() {
  // Check WiFi Status
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;  //Object of class HTTPClient
    http.begin("http://jsonplaceholder.typicode.com/users/5");
    int httpCode = http.GET();
    //Check the returning code
    if (httpCode > 0) {
      // Get the request response payload
      String payload = http.getString();
      Serial.println(payload);
      
      // TODO: Parsing
      const size_t capacity = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
      DynamicJsonDocument doc(capacity);

      // load payload into a char array
      char* json; 
      json = new char[capacity];
      payload.toCharArray(json, capacity);

      // extract the json into the DynamicJsonDocument object
      deserializeJson(doc, json);

      
      int id = doc["id"]; // 5
      const char* name = doc["name"]; // "Chelsey Dietrich"
      const char* username = doc["username"]; // "Kamren"
      const char* email = doc["email"]; // "Lucio_Hettinger@annie.ca"

      JsonObject address = doc["address"];
      const char* address_street = address["street"]; // "Skiles Walks"
      const char* address_suite = address["suite"]; // "Suite 351"
      const char* address_city = address["city"]; // "Roscoeview"
      const char* address_zipcode = address["zipcode"]; // "33263"

      const char* address_geo_lat = address["geo"]["lat"]; // "-31.8129"
      const char* address_geo_lng = address["geo"]["lng"]; // "62.5342"

      const char* phone = doc["phone"]; // "(254)954-1289"
      const char* website = doc["website"]; // "demarco.info"
      
      JsonObject company = doc["company"];
      const char* company_name = company["name"]; // "Keebler LLC"
      const char* company_catchPhrase = company["catchPhrase"]; // "User-centric fault-tolerant solution"
      const char* company_bs = company["bs"]; // "revolutionize end-to-end systems"

     if(strcmp(phone, "(254)954-1289")==0){
      Serial.println("you got it");
     }

    }

    http.end();   //Close connection
  }
  // Delay
  delay(60000);
}
