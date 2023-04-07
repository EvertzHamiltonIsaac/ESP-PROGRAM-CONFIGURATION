//Librerias que Utilizara el proyecto
//-----------------------------------------------------------
#include <Arduino.h>
#if defined(ESP32) || defined(ARDUINO_RASPBERRY_PI_PICO_W)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
//-----------------------------------------------------------
#include <Firebase_ESP_Client.h>
//Librerias que Utilizara el proyecto

//RTDB, Libreria de Ayuda o Apoyo.
#include <addons/RTDBHelper.h>

//Credenciales del Internet
#define WIFI_SSID "Amanda"
#define WIFI_PASSWORD "Morena00000010"

//URL de la Base de datos en Firebase
#define DATABASE_URL "final-project-web-v0-default-rtdb.firebaseio.com"

//ESP8266 physical outputs
#define BIT_0 16 //D0 of ESP8266
#define BIT_1 5  //D1 of ESP8266
#define BIT_2 4  //D2 of ESP8266
#define BIT_3 0  //D3 of ESP8266

//Variables constantes declaradas
#define IP_ESP "1111:DB1:1111::"
#define PATH_ESP "1111:DB1:1111::/ESP_NAME"
#define ESP_NAME "TEST-MODULE-1"

bool IsESPCreated = false;

// Define el Objeto Firebase
FirebaseData fbdo;

// Define objeto FirebaseAuth para athenticacion de datos.
FirebaseAuth auth;

/* Define objeto de FirebaseConfig para la configuracion de datos. */
FirebaseConfig config;

// Variable Long para gestionar los Delays.
unsigned long dataMillis = 0;
int count = 0;

#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
WiFiMulti multi;
#endif

void STARTUP(){
  Serial.begin(115200);

#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
  multi.addAP(WIFI_SSID, WIFI_PASSWORD);
  multi.run();
#else
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
#endif

  Serial.print("Connecting to Wi-Fi");
  unsigned long ms = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
      Serial.print(".");
      delay(300);
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
      if (millis() - ms > 10000)
          break;
#endif
  }

  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the database URL(required) */
  config.database_url = DATABASE_URL;
  config.signer.test_mode = true;

#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
  config.wifi.clearAP();
  config.wifi.addAP(WIFI_SSID, WIFI_PASSWORD);
#endif

  Firebase.reconnectWiFi(true); //Reconexion a Wifi Habilitada.
  Firebase.begin(&config, &auth); // Inicia la configuracion y la autenticacion.

  pinMode(BIT_0, OUTPUT);
  pinMode(BIT_1, OUTPUT);
  pinMode(BIT_2, OUTPUT);
  pinMode(BIT_3, OUTPUT);
}

void detectYourself(){

  String nameOfEsp = String(Firebase.RTDB.get(&fbdo, PATH_ESP));
  String s = fbdo.to<String>();

  Serial.println(s);
  if(s == ESP_NAME){
      Serial.println("ESP Local Information");
      Serial.println("IP: " + String(IP_ESP));
      Serial.println("PATH IN DATABASE " + String(PATH_ESP));
      Serial.println("ESP NAME: " + String(ESP_NAME));
      IsESPCreated = true;
    }else{
      Serial.print("The ESP are not vinculated with the database.");
      IsESPCreated = false;
    }
}

void setup(){
  STARTUP();
  detectYourself();
}


String binary = "";

void loop()
{
  if(IsESPCreated == true){
/*-------------------------------------B0-------------------------------------*/
    if (millis() - dataMillis > 500){
      dataMillis = millis();

	    for(int i = 0; i <= 3; i++){
		    if (Firebase.RTDB.getBool(&fbdo, "1111:DB1:1111::/B" + String(i))) {
          if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_boolean) {
            if(fbdo.to<bool>() == true){
              //Serial.println("B0: " + String(i));
              binary += "1";
              delay(250);
            }
            else {
              binary += "0";
              //Serial.println("B0: " + String(i));
              delay(250);
            }
		      }
        } else {
          Serial.println(fbdo.errorReason());
        }
	    }
	      Serial.println("Output: " + binary); 
    }

    if(binary == "0000"){
        digitalWrite(BIT_0,0);
        digitalWrite(BIT_1,0);
        digitalWrite(BIT_2,0);
        digitalWrite(BIT_3,0);
      }
    if(binary == "0001"){
        digitalWrite(BIT_0,0);
        digitalWrite(BIT_1,0);
        digitalWrite(BIT_2,0);
        digitalWrite(BIT_3,1);
      }
    if(binary == "0010"){
        digitalWrite(BIT_0,0);
        digitalWrite(BIT_1,0);
        digitalWrite(BIT_2,1);
        digitalWrite(BIT_3,0);
      } 
    if(binary == "0011"){
        digitalWrite(BIT_0,0);
        digitalWrite(BIT_1,0);
        digitalWrite(BIT_2,1);
        digitalWrite(BIT_3,1);
      }
    if(binary == "0100"){
        digitalWrite(BIT_0,0);
        digitalWrite(BIT_1,0);
        digitalWrite(BIT_2,0);
        digitalWrite(BIT_3,1);
      }
    if(binary == "0101"){
        digitalWrite(BIT_0,0);
        digitalWrite(BIT_1,1);
        digitalWrite(BIT_2,0);
        digitalWrite(BIT_3,1);
      }
    if(binary == "0110"){
        digitalWrite(BIT_0,0);
        digitalWrite(BIT_1,1);
        digitalWrite(BIT_2,1);
        digitalWrite(BIT_3,0);
      }
    if(binary == "0111"){
        digitalWrite(BIT_0,0);
        digitalWrite(BIT_1,1);
        digitalWrite(BIT_2,1);
        digitalWrite(BIT_3,1);
      }
    else if(binary == "1000"){
        digitalWrite(BIT_0,1);
        digitalWrite(BIT_1,0);
        digitalWrite(BIT_2,0);
        digitalWrite(BIT_3,0);
      }
    if(binary == "1001"){
        digitalWrite(BIT_0,1);
        digitalWrite(BIT_1,0);
        digitalWrite(BIT_2,0);
        digitalWrite(BIT_3,1);
      }
    if(binary == "1010"){
        digitalWrite(BIT_0,1);
        digitalWrite(BIT_1,0);
        digitalWrite(BIT_2,1);
        digitalWrite(BIT_3,0);
      }
    if(binary == "1011"){
        digitalWrite(BIT_0,1);
        digitalWrite(BIT_1,0);
        digitalWrite(BIT_2,1);
        digitalWrite(BIT_3,1);
      }
    if(binary == "1100"){
        digitalWrite(BIT_0,1);
        digitalWrite(BIT_1,1);
        digitalWrite(BIT_2,0);
        digitalWrite(BIT_3,0);
      }
    if(binary == "1101"){
        digitalWrite(BIT_0,1);
        digitalWrite(BIT_1,1);
        digitalWrite(BIT_2,0);
        digitalWrite(BIT_3,1);
      } 
    if(binary == "1110"){
        digitalWrite(BIT_0,1);
        digitalWrite(BIT_1,1);
        digitalWrite(BIT_2,1);
        digitalWrite(BIT_3,0);
      }
    if(binary == "1111"){
        digitalWrite(BIT_0,1);
        digitalWrite(BIT_1,1);
        digitalWrite(BIT_2,1);
        digitalWrite(BIT_3,1);
      }
      binary = "";
    }
  else { Serial.print("The ESP are not vinculated with the database."); }
}