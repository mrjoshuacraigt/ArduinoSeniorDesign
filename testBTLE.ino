#include <CurieBLE.h>

//create peripheral instance
BLEPeripheral blePeripheral;

//Node Serivce
BLEService nodeService("19B10070-E8F2-537E-4F6C-D104768A1214");

//Node ID characteristic and allow remote device to read from it 
BLECharCharacteristic nodeIDCharacteristic("19B10071-E8F2-537E-4F6C-D104768A1214", BLERead);

//DistanceMaster characteristic and allow remote device to read from it 
BLECharCharacteristic distanceMasterCharacteristic("19B10072-E8F2-537E-4F6C-D104768A1214", BLERead);

//DistanceP1 characteristic and allow remote device to read from it 
BLECharCharacteristic distanceP1Characteristic("19B10073-E8F2-537E-4F6C-D104768A1214", BLERead);

//DistanceP2 characteristic and allow remote device to read from it 
BLECharCharacteristic distanceP2Characteristic("19B10074-E8F2-537E-4F6C-D104768A1214", BLERead);

//Sensor Service
BLEService sensorService("19B10080-E8F2-537E-4F6C-D104768A1214");

//Sensor Node ID characteristic identifies the node the sensor belongs to
BLECharCharacteristic sensorNodeIDCharacteristic("19B10081-E8F2-537E-4F6C-D104768A1214", BLERead);

//Sensor Type characteristic identifies the node the sensor belongs to
BLECharCharacteristic sensorTypeCharacteristic("19B10082-E8F2-537E-4F6C-D104768A1214", BLERead);

//Sensor Reading characteristic identifies the reading from the sensor
BLECharCharacteristic sensorReadingCharacteristic("19B10083-E8F2-537E-4F6C-D104768A1214", BLERead);


void setup() {
  Serial.begin(9600);

  //set the local name peripheral advertises
  blePeripheral.setLocalName("Master Node");
  //set the UUID for the service this peripheral advertises
  blePeripheral.setAdvertisedServiceUuid(nodeService.uuid());

  //add service and characteristics
  blePeripheral.addAttribute(nodeService);
  blePeripheral.addAttribute(nodeIDCharacteristic);
  blePeripheral.addAttribute(distanceMasterCharacteristic);
  blePeripheral.addAttribute(distanceP1Characteristic);
  blePeripheral.addAttribute(distanceP2Characteristic);
  blePeripheral.addAttribute(sensorService);
  blePeripheral.addAttribute(sensorNodeIDCharacteristic);
  blePeripheral.addAttribute(sensorTypeCharacteristic);
  blePeripheral.addAttribute(sensorReadingCharacteristic);

}

void loop() {
  // put your main code here, to run repeatedly:

}
