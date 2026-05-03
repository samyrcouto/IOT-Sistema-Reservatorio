CREATE DATABASE iot_monitoramento;
 
USE iot_monitoramento;
 
CREATE TABLE sensores (
  id INT AUTO_INCREMENT PRIMARY KEY,
  temperatura FLOAT,
  distancia FLOAT,
  data TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);