#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <DHT.h>

// ===== DHT =====
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ===== WIFI =====
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ===== MQTT (HiveMQ Cloud) =====
const char* mqtt_server = "d82a50269f9f4615a25eb0e03f5807a9.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;

const char* mqtt_user = "estufa";
const char* mqtt_pass = "171314Sam";

const char* topic = "estufa/dados";

// ===== OBJETOS =====
WiFiClientSecure espClient;
PubSubClient client(espClient);

// ===== SETUP =====
void setup() {
  Serial.begin(115200);
  dht.begin();

  Serial.println("Iniciando...");

  // WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi OK");

  // TLS (modo simplificado)
  espClient.setInsecure();

  // MQTT
  client.setServer(mqtt_server, mqtt_port);
}

// ===== RECONEXÃO MQTT =====
void reconnect() {
  while (!client.connected()) {
    Serial.println("Tentando MQTT...");

    if (client.connect("esp32_estufa", mqtt_user, mqtt_pass)) {
      Serial.println("MQTT OK");
    } else {
      Serial.print("Falhou, rc=");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

// ===== LOOP =====
void loop() {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Erro ao ler DHT!");
    return;
  }

  String payload = "{";
  payload += "\"temperatura\":" + String(temp) + ",";
  payload += "\"umidade\":" + String(hum);
  payload += "}";

  Serial.println(payload);

  boolean ok = client.publish("estufa/dados", payload.c_str());

  if (ok) {
    Serial.println("Enviado com sucesso");
  } else {
    Serial.println("Erro ao enviar");
  }

  delay(5000); 
}
