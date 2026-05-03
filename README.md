# 🚀 Monitoramento Inteligente com IoT (ESP32 + MQTT + Node-RED)

## 📌 Descrição do Projeto

Este projeto tem como objetivo desenvolver uma solução de monitoramento inteligente utilizando conceitos de Internet das Coisas (IoT).

O sistema realiza a coleta de dados de sensores (temperatura e distância), envia essas informações via protocolo MQTT, processa os dados no Node-RED, exibe em um dashboard em tempo real e armazena os dados em um banco de dados MySQL.

---

## 🎯 Objetivo

Criar um sistema completo de monitoramento que contemple:

* Aquisição de dados com ESP32
* Comunicação via MQTT
* Processamento com Node-RED
* Visualização em dashboard
* Armazenamento em banco de dados
* Integração com API externa

---

## 🧱 Arquitetura da Solução

```
ESP32 (Wokwi)
   ↓
MQTT (Broker HiveMQ)
   ↓
Node-RED
   ↓
Dashboard em tempo real
   ↓
MySQL (armazenamento)
   ↓
API externa (dados climáticos)
```

---

## 🛠️ Tecnologias Utilizadas

* ESP32 (simulado no Wokwi)
* MQTT (HiveMQ)
* Node-RED
* MySQL
* API de clima (OpenWeather)
* Arduino IDE

---

## 🔌 Sensores Utilizados

* 🌡️ Sensor de Temperatura (DHT22)
* 📏 Sensor de Distância (Ultrassônico HC-SR04)

---

## ⚙️ Funcionalidades

* Coleta de dados em tempo real
* Envio de dados via MQTT
* Dashboard com:

  * Gauge (indicadores)
  * Gráficos em tempo real
* Sistema de alertas (ex: temperatura alta)
* Armazenamento de dados no MySQL
* Integração com API externa (clima)

---

## 🗄️ Banco de Dados

### 📌 Estrutura

```sql
CREATE DATABASE iot_monitoramento;

USE iot_monitoramento;

CREATE TABLE sensores (
  id INT AUTO_INCREMENT PRIMARY KEY,
  temperatura FLOAT,
  distancia FLOAT,
  data TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
```

---

## ▶️ Como Executar o Projeto

### 1. Iniciar o banco de dados

* Abrir o XAMPP
* Iniciar o MySQL
* Criar o banco e tabela

---

### 2. Rodar o Node-RED

* Executar:

```
node-red
```

* Acessar:

```
http://localhost:1880
```

---

### 3. Importar o fluxo

* Menu → Import → Selecionar `flow.json`

---

### 4. Configurar MQTT

* Broker: `broker.hivemq.com`
* Tópicos:

  * `maquina1/temperatura`
  * `maquina1/distancia`

---

### 5. Executar o ESP32 (Wokwi)

* Abrir o projeto no Wokwi
* Iniciar a simulação
* Ajustar valores dos sensores

---

### 6. Acessar o Dashboard

```
http://localhost:1880/ui
```

---

## 📊 Dashboard

O dashboard apresenta:

* Temperatura em tempo real
* Distância em tempo real
* Gráficos históricos
* Alertas automáticos
* Dados externos (clima)

---

## 🎥 Vídeo Youtube

🔗 Link: 

---

## 📁 Estrutura do Projeto

```
/iot-estufa
 ├── esp32/
 │     └── codigo.ino
 ├── node-red/
 │     └── flow.json
 ├── database/
 │     └── script.sql
 ├── README.md
```

---

## 👨‍💻 Alunos

* Lucas Rafael Solimene / RM: 565194
* Samyr Couto Oliveira / RM: 565562

---
