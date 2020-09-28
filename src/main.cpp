#include <arduino.h>
#include <esp8266wifi.h>

#include <PubSubClient.h>
#include <Adafruit_Sensor.h>                       // Biblioteca DHT Sensor Adafruit 
#include <DHT.h>
#include <DHT_U.h>

#include <ArduinoJson.h>

const char* ssid     = "HOME";
const char* password = "123456789";   

float temperatura = 0;
String Str = "temperatura";


#define DHTTYPE DHT11                           // Sensor DHT11  
#define DHTPIN 4                                // Pino D1
DHT_Unified dht(DHTPIN, DHTTYPE);               // configurando o Sensor DHT - pino e tipo

#define LEDPIN 14                               // Pino D5 (Recebimento de Mensagens)
 

int wifiStatus;


unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 2000;           // interval at which to blink (milliseconds)
 
//**************************************
 
//__ Configurações para o IBM Watson
 
//**************************************
 
//__ Informações do dispositivo
 
#define DEVICE_TYPE  "sensortemp"
#define DEVICE_ID    "D1"

#define DEVICE_ID_IN    "led"

 
//__ Informações da conexão com o servidor
 
#define ORG     "bfzzmh"

//__ Dados da API

char authMeth[] = "a-bfzzmh-5v9rsqqer2";
#define TOKEN   "fmpfj)cBX8RA&TKhew"

//__ Variáveis de conexão com o servidor (Não customizaveis)
 
char host[]   = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[]    = "iot-2/type/" DEVICE_TYPE "/id/" DEVICE_ID "/evt/1-anl/fmt/json";
char topicIn[]    = "iot-2/type/" DEVICE_TYPE "/id/" DEVICE_ID_IN "/evt/1-anl/fmt/json";
char token[]    = TOKEN;
char clientId[] = "a:" ORG ":" DEVICE_ID;

//__ Inicia WiFi
 
WiFiClient wifiClient;
PubSubClient client(host, 1883, NULL, wifiClient);

DynamicJsonDocument doc(1024);                    // Variável para Converter o Json recebido

void callback(char* topicIn, byte* payload, unsigned int length) {

  Serial.print("Message arrived [");
  Serial.print(topicIn);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  
  deserializeJson(doc, payload);

  int val = doc["d"]["led"];
  Serial.print("Led: "); 
  Serial.println(val); 

  if (val == 1){
  
  digitalWrite(LEDPIN, HIGH);
  
  } else if( val == 0 ){
 
  digitalWrite(LEDPIN, LOW);
  
  }

  Serial.println();
 // delay(2000);
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(clientId, authMeth, token)) {
      Serial.println("connected");
      // ... and resubscribe
      client.subscribe(topicIn);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      // Wait 2 seconds before retrying
      delay(2000);
    }
  }
}



void setup() {
 
 pinMode(LEDPIN, OUTPUT);

  //__ Inicializa a serial
  
  Serial.begin(9600);
  Serial.println();
  Serial.print("Conectando-se na rede ");
  Serial.print(ssid);
  
  //__ Conecta-se na rede WIFI
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  
  Serial.print("Conectado, endereço de IP: ");
  Serial.println(WiFi.localIP());
  
  //inicia DHT
  
  dht.begin();

  client.setCallback(callback);

  // Allow the hardware to sort itself out
  delay(1500);

  
}

//__ Envia os dados para a cloud


 
void enviaDado(float dado){
 
  String payload = "{\"d\":{\"" + Str + "\":";
 
  payload += dado;
  payload += "}}";
 
  Serial.print("Sending payload: ");
  Serial.println(payload);
 
 //__ Envia o dado
 
  if (client.publish(topic, (char*) payload.c_str())) {
    Serial.println("Publish ok");
  } else {
    Serial.println("Publish failed");
  }
 
}


 
void loop() {

  unsigned long currentMillis = millis();
  if (!client.connected()) {
    reconnect();
  }

  client.loop(); 

  //__ Le Sensores
  //temperatura = LeTemperatura();

  sensors_event_t event;                        // inicializa o evento da Temperatura
  dht.temperature().getEvent(&event);           // faz a leitura da Temperatura
  if (isnan(event.temperature))                 // se algum erro na leitura
  {
    Serial.println("Erro na leitura da Temperatura!");
  }

 else 
  {
   temperatura =  event.temperature;

   //__ Envia um dado para a cloud
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    enviaDado(temperatura);
  }

  }

  

   
}

