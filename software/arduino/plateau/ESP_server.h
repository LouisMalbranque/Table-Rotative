#include "arduino.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "constantes.h"


// définition des UUIDs
#define SERVICE_UUID        "1c1e2ea0-7c18-4c35-b38d-04aa84086d66"
#define CHARACTERISTIC_UUID "238df85b-af2f-4817-841f-7ce4330ad0a8"




class ESP_server{
  private:
    String data;    // data stockée dans les charactéristiques
    int values[11]; // valeurs décodées
    BLEServer *pServer; 
    BLEService *pService; 
    BLEAdvertising *pAdvertising; 
    BLECharacteristic *pcharacteristic;
  public:
    ESP_server(); // constructeur par défaut
    void begin(); // démarrage du serveur
    String read(); // lecture depuis les characs
    String getData(); // renvoie la data
    int getValue(int i); // renvoie la valeur décodée à l'indice i
    void writeData(String s); // écrit dans la data
    void decode(); // décode
};
