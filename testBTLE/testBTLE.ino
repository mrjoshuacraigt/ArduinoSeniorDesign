
#include <CurieBLE.h>
#include <string.h>

//create peripheral instance
BLEPeripheral blePeripheral;

//Node Serivce
BLEService nodeService("19B10070-E8F2-537E-4F6C-D104768A1214");

//Node ID characteristic and allow remote device to read from it 
BLEIntCharacteristic nodeIDCharacteristic("19B10071-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);

//DistanceFromMaster characteristic and allow remote device to read from it 
BLEFloatCharacteristic distanceFromMasterCharacteristic("19B10074-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);

//Sensor Service
BLEService sensorService("19B10080-E8F2-537E-4F6C-D104768A1214");

//Sensor Node ID characteristic identifies the node the sensor belongs to
BLEFloatCharacteristic sensorNodeIDCharacteristic("19B10081-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);

//Sensor Type characteristic identifies the node the sensor belongs to
BLEFloatCharacteristic sensorTypeCharacteristic("19B10082-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);

//Sensor Reading characteristic identifies the reading from the sensor
BLEFloatCharacteristic sensorReadingCharacteristic("19B10083-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);

boolean readReady = false;
String message;



void setup() {
  Serial.begin(9600);

  while(!Serial);

  Serial1.begin(230400);

  //set the local name and serive UUID:
  blePeripheral.setLocalName("Master Node");
  blePeripheral.setAdvertisedServiceUuid(nodeService.uuid());

  //add Node Service and characteristics
  blePeripheral.addAttribute(nodeService);
  blePeripheral.addAttribute(nodeIDCharacteristic);
  blePeripheral.addAttribute(distanceFromMasterCharacteristic);

  //add Sensor Serivce and characteristics
  blePeripheral.addAttribute(sensorService);
  blePeripheral.addAttribute(sensorNodeIDCharacteristic);
  blePeripheral.addAttribute(sensorTypeCharacteristic);
  blePeripheral.addAttribute(sensorReadingCharacteristic);

  // set the initial value for the characteristics
  nodeIDCharacteristic.setValue(0);
  distanceFromMasterCharacteristic.setValue(0);
  sensorNodeIDCharacteristic.setValue(0);
  sensorTypeCharacteristic.setValue(0);
  sensorReadingCharacteristic.setValue(0);


  // begin advertising BLE service:
  blePeripheral.begin();

  Serial.println("BLE Master Node");

  Serial.println("Bluetooth device active, waiting for connections...");

  

  

}

void loop() {

  BLECentral central = blePeripheral.central();

  if (readReady && central.connected()) {
        Serial.println(message);
        splitString(message);
        readReady = false;
  }



}

void serialEvent1() {
  message = Serial1.readString();
  readReady = true;
}

void splitString(String readingString) {

  String nodeId;
  String distance;
  String numOfNodes;

  Serial.println("hi");
  // parse readingString
  int str_len = readingString.length() + 1;
  char inputMessage[100];
  readingString.toCharArray(inputMessage, 100);
  
  char * pch;
  pch = strtok(inputMessage,":");
  int count = 0;
  while (pch != NULL)
  {
    String pch_string = String(pch);
    Serial.println(pch_string);
    pch = strtok (NULL, ":");
    if (count == 0) {
      nodeId = pch_string;
    } else if (count == 1) {
      distance = pch_string;
      sendNodeService(nodeId, distance);
    } else if (count == 2) {
      if (isValidReading(pch)){
        sendSenorService(nodeId, "0", pch_string); 
      }
    } else if (count == 3) {
      if (isValidReading(pch)){
        sendSenorService(nodeId, "1", pch_string);
      }
    } else if (count == 4) {
      if (isValidReading(pch)){
        sendSenorService(nodeId, "2", pch_string);
      }
    } else if (count == 5) {
      if (isValidReading(pch)){
        sendSenorService(nodeId, "3", pch_string);
      }
    }
    count++;
  }
}

void sendNodeService(String nodeId, String distance) {

  Serial.println("sendNodeService");
  nodeIDCharacteristic.setValue(nodeId.toInt());
  distanceFromMasterCharacteristic.setValue(distance.toFloat());
  
}

void sendSenorService(String nodeId, String sensorType, String sensorReading) {
  
  sensorNodeIDCharacteristic.setValue(nodeId.toFloat());
  sensorTypeCharacteristic.setValue(sensorType.toFloat());
  
  sensorReadingCharacteristic.setValue(sensorReading.toFloat());
  
   
}

boolean isValidReading(String reading) {

  if (reading.compareTo("NOV")){
    return false;
  }

  return true;
  
}



