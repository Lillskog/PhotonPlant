// This #include statement was automatically added by the Particle IDE.
#include "dht11.h"

#include "ThingSpeak.h"
#include "dht11.h"      // https://playground.arduino.cc/Main/DHT11Lib
#include "Particle.h"

dht11 DHT11;
TCPClient client;

#define DHT11PIN 2  // pin 2 is used as the data pin to communicate with the DHT11 board

long delayTime = 60000; // ~9 minute delay 550000
unsigned long startMillis; // variable to store the time at start of counting
const char * eventName = "temphum"; // Event name defined in WebHook 
unsigned long myChannelNumber = XXXXXX; // ThingSpeak Channel number (ADD YOUR OWN!)
const char * myWriteAPIKey = "XXXXXXXXXXXX"; // ThingSpeak write API (ADD YOUR OWN!)
// ThingSpeak http://www.geothread.net/using-thingspeak-and-a-particle-photon/

const int MIN_LIGHT = 500;  // 3.3v 500
const int MAX_LIGHT = 4100; // 3.3v 1800

const int AIR_VALUE = 3800;  // 3.3v 520 
const int WATER_VALUE = 1900;    // 3.3v 260
const int INTERVAL = (AIR_VALUE - WATER_VALUE)/3;

int soilMoistureValue = 0;
int soilMoisturePin = A0;
int percentage_soil;

int photoresistor = A2;
int photovalue;
int percentage_bright;

void setup() {
    pinMode(photoresistor,INPUT);
    pinMode(soilMoisturePin, INPUT);
    
    startMillis = millis();
    ThingSpeak.begin(client);
    delay(5000); // setup delay
}

void clearCounter() {
    startMillis = millis();
}

void readTempHum() {
    int chk = DHT11.read(DHT11PIN); // check status of DHT11
    // some debug outputs
    Particle.publish("DEBUG", "Read sensor: ");
    switch (chk)
    {
    case DHTLIB_OK: 
        Particle.publish("DEBUG", "OK");
    	break;
    case DHTLIB_ERROR_CHECKSUM: 
        Particle.publish("DEBUG", "Checksum error");
    	break;
    case DHTLIB_ERROR_TIMEOUT: 
    	Particle.publish("DEBUG", "Time out error");
    	break;
    default: 
    	Particle.publish("DEBUG", "Unknown error");
    	break;
    }

    delay(1000); // DHT11 requires a short delay to fetch the data
    
    int t = DHT11.temperature;
    int h = DHT11.humidity;
    
    ThingSpeak.setField(1,t);
    ThingSpeak.setField(2,h);
}

void readLight() {
    photovalue = analogRead(photoresistor);
    percentage_bright = map(photovalue, MIN_LIGHT, MAX_LIGHT, 0, 100);
    
    ThingSpeak.setField(3,percentage_bright);
    
}

void readSoil() {
    soilMoistureValue= analogRead(soilMoisturePin);
    percentage_soil = map(soilMoistureValue, WATER_VALUE, AIR_VALUE, 100, 0);
    
    ThingSpeak.setField(4,percentage_soil);
}

void loop() {
    // non-blocking timer loop
    // cant do a normal delay here as the Photon doesn't like it
    // when you block it from talking to the server for more than 10 seconds
    if (millis() - startMillis >= delayTime) {
        // if delayTime as elapsed, clear counter and take readings
        clearCounter();
        readTempHum();
        readLight();
        readSoil();
        ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey); 
    }
    
    delay(1000);
}
