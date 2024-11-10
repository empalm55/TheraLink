// BLE
#include <ArduinoBLE.h>

// Configure services
// UUID Generator: https://www.uuidgenerator.net/version7
/*
  019311c2-02cc-707e-a47d-f51ae7000016  // Service
  019311c2-02cc-7a12-8e0d-3910e3ea7726    // led
*/
// Servicio Bluetooth Low Energy para Temperatura y Humedad
BLEService bleService("019311c2-02cc-707e-a47d-f51ae7000016");

// Caracterisiticas Bluetooth Low Energy
/*
  019311c2-02cc-7a12-8e0d-3910e3ea77p1 //potentiometer service
*/
BLEUnsignedCharCharacteristic potChar("019311c2-02cc-7a12-8e0d-3910e3ea77p1", BLERead | BLENotify);
//BLEUnsignedCharCharacteristic forceChar("019311c2-02cc-7a12-8e0d-3910e3ea77p2", BLERead | BLENotify);

int oldPotValue = 0;
//int oldForceLevel = 0;
long previousMillis = 0;
