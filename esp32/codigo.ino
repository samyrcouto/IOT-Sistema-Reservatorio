#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
 
// WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";
 
// MQTT
const char* mqtt_server = "broker.hivemq.com";
 
// DHT
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
 
// Ultrassônico
#define TRIG 5
#define ECHO 18
 
WiFiClient espClient;
PubSubClient client(espClient);
 
// Controle de tempo
unsigned long lastRead = 0;
const long interval = 3000;
 
void setup_wifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}
 
void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32Client-Wokwi")) {
      Serial.println("Conectado ao MQTT!");
    } else {
      Serial.println("Falha MQTT, tentando novamente...");
      delay(2000);
    }
  }
}
 
float getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
 
  long duration = pulseIn(ECHO, HIGH, 30000); // timeout de segurança
 
  // Se não detectar nada
  if (duration == 0) {
    return 400.0;
  }
 
  float distance = duration * 0.03 / 2;
 
  // Limitar valores
  if (distance > 400) distance = 400;
  if (distance < 0) distance = 0;
 
  return distance;
}
 
void setup() {
  Serial.begin(115200);
 
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
 
  dht.begin();
 
  setup_wifi();
  client.setServer(mqtt_server, 1883);
 
  delay(2000);
}
 
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
 
  if (millis() - lastRead >= interval) {
    lastRead = millis();
 
    float temperatura = dht.readTemperature();
    float distancia = getDistance();
 
    // Validação DHT
    if (isnan(temperatura)) {
      Serial.println("Erro ao ler temperatura!");
      return;
    }
 
    // Converter para string
    char tempString[8];
    dtostrf(temperatura, 1, 2, tempString);
 
    char distString[8];
    dtostrf(distancia, 1, 2, distString);
 
    // Publicar MQTT
    client.publish("maquina1/temperatura", tempString);
    client.publish("maquina1/distancia", distString);
 
    // Logs
    Serial.println("--------");
    Serial.println("Temperatura: " + String(tempString) + " °C");
 
    if (distancia >= 400) {
      Serial.println("Distância: Fora de alcance");
    } else {
      Serial.println("Distância: " + String(distString) + " cm");
    }
  }
}