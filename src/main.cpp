#include <arduino.h>
#include <esp8266wifi.h>

#include <PubSubClient.h>
#include <Adafruit_Sensor.h>                       // Biblioteca DHT Sensor Adafruit 
#include <DHT.h>
#include <DHT_U.h>

 
const char* ssid     = "HOME";
const char* password = "123456789";   

float temperatura = 0;
String Str = "temperatura";


#define DHTTYPE DHT11                           // Sensor DHT11  
#define DHTPIN 5
DHT_Unified dht(DHTPIN, DHTTYPE);               // configurando o Sensor DHT - pino e tipo
 

int wifiStatus;
 
//**************************************
 
//__ Configurações para o IBM Watson
 
//**************************************
 
//__ Informações do dispositivo
 
#define DEVICE_TYPE  "SensorDht11NodeMCU"
#define DEVICE_ID    "D1"
 
//__ Informações da conexão com o servidor
 
#define ORG     "tzr7bt"
#define TOKEN   "TXsWjrJDR9R_V3tMIw"

//__ Variáveis de conexão com o servidor (Não customizaveis)
 
char server[]   = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[]    = "iot-2/type/" DEVICE_TYPE "/id/" DEVICE_ID "/evt/1-anl/fmt/json";
char authMeth[] = "a-tzr7bt-bb5l9uvp8k";
char token[]    = TOKEN;
char clientId[] = "a:" ORG ":" DEVICE_ID;

//__ Inicia WiFi
 
WiFiClient wifiClient;
PubSubClient client(server, 1883, NULL, wifiClient);


void setup() {
 
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
 
}

//__ Envia os dados para a cloud

// JSON: Ex:
//  {"d":{"temperatura":20}}
 
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

  //__ Verifica se está conectada a cloud para envio dos dados
 
  if (!!!client.connected()) {
 
  //__ Caso não esteja conectada, tenta a conexão
  Serial.print("Reconectando-se em ");
  Serial.println(server);
 
  while (!!!client.connect(clientId, authMeth, token)) {
    Serial.print(".");
    delay(500);
 
  }
 
  Serial.println();
 
 }
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
  }

  //__ Envia um dado para a cloud
  
  enviaDado(temperatura);

  //__ Faz o envio a cada 2 segundos.
  
  delay(2000);
 
}

