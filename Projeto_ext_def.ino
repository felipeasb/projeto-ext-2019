
#include <DHT.h> 
#include <ESP8266WiFi.h> 
#include <PubSubClient.h> 
#include <TimeLib.h>


////////////////////////////////////////////////////////////////////////////////////////////

//Sets

#define TOPICO_SUBSCRIBE "cefet/lab/01"
#define TOPICO_PUBLISH "banheirodtinf/lab/01" 
#define ID_MQTT "dtinf"    
#define DHTPIN 2      
#define DHTTYPE DHT11
#define PIRPIN 5
#define SENSLUM 12

//NodeMCU pin mapping
#define D0    16
#define D1    5
#define D2    4
#define D3    0
#define D4    2
#define D5    14
#define D6    12
#define D7    13
#define D8    15
#define D9    3
#define D10   1
 
 
// WIFI
const char* SSID = "SSID"; 
const char* PASSWORD = "*******"; 
  
// MQTT
const char* BROKER_MQTT = "mqtt.eclipse.org"; 
int BROKER_PORT = 1883; 
 
 
//Global
WiFiClient espClient; 
PubSubClient MQTT(espClient); 
DHT dht(DHTPIN, DHTTYPE);
float umi = dht.readHumidity();
float temp = dht.readTemperature();
int pirstate;

/////////////////////////////////////////////////////////////////////////////////////////////
  
//Functions
void SerialBegin();
void WiFiInit();
void MQTTInit();
void WiFireconnect(); 
void MQTTreconnect():
void WiFiMQTTCheck(void);
 
/////////////////////////////////////////////////////////////////////////////////////////////

void setup() 
{
    //inicializações:
    SerialBegin();
    WiFiInit();
    MQTTInit();
    dht.begin();
}

////////////////////////////////////////////////////////////////////////////////////////////
  
//Inicializa o monitor serial
void SerialBegin() 
{
    Serial.begin(115200);
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Conexão com rede WiFi (usando a função de reconexão)
void WiFiInit() 
{
    delay(10);
    Serial.print("Estabelecendo conexão com: ");
    Serial.println(SSID);
    Serial.println("...");
     
    WiFireconnect();
}

/////////////////////////////////////////////////////////////////////////////////////////////
  

void MQTTInit() 
{
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);         
    MQTT.connect(ID_MQTT);
}

/////////////////////////////////////////////////////////////////////////////////////////////
  

void MQTTreconnect() 
{
    while (!MQTT.connected()) 
    {
        Serial.print("Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) 
        {
            Serial.println("Conectado!");
            MQTT.subscribe(TOPICO_SUBSCRIBE); 
        } 
        else
        {
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Nova tentativa em 2s");
            delay(2000);
        }
    }
}


////////////////////////////////////////////////////////////////////////////////////////////

void WiFireconnect() 
{
    if (WiFi.status() == WL_CONNECTED)
        return;
         
    WiFi.begin(SSID, PASSWORD); 
     
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(100);
        Serial.print(".");
    }
   
    Serial.println();
    Serial.print("Conectado com sucesso a rede ");
    Serial.print(SSID);
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
}

////////////////////////////////////////////////////////////////////////////////////////////

//Verifica se o WiFi e broker do MQTT estão conectados
void WiFIMQTTCheck(void)
{
    if (!MQTT.connected()) 
     reconnectMQTT();
     
     reconectWiFi();
}

////////////////////////////////////////////////////////////////////////////////////////////

//Função do detector de presença
void PIR(void)
{    
     
  if (digitalRead(PIRPIN)== HIGH)
  {
    pirstate = 1;
  }
  else
  {
    pirstate = 0;
  }
}
 
////////////////////////////////////////////////////////////////////////////////////////////

void OutputMQTT(void)
{
    timeClient.update();
    timeClient.getEpochTime(); 
    Serial.println(timeClient.getEpochTime());

    int valorSensLum = analogRead(SENSLUM);
    
    unsigned long t = timeClient.getEpochTime();
    char buff[32];
    
    sprintf(buff, "%02d-%02d-%02d %02d:%02d:%02d", day(t), month(t), year(t), hour(t), minute(t), second(t));

    String mensagem = '{"Local": "lab01","datahora": "'+buff+'","temperatura": "'+ (float)temp +'","umidade": "'+ (float)umi +'", "presenca": "pirstate", luminosidade": "valorSensLum",}';
    const char* mensagem_final = mensagem.c_str();

    MQTT.publish(TOPICO_PUBLISH, mensagem_final);
    Serial.println(mensagem_final);
    
}
 
/////////////////////////////////////////////////////////////////////////////////////////////
 
void loop() 
{   
    
    VerificaConexoesWiFIEMQTT();
   
    EnviaEstadoOutputMQTT();
 
    MQTT.loop();
}
