#include <Particle.h>
#include <math.h>

const int MIN_LIGHT = 500;
const int MAX_LIGHT = 1800;

int photoresistor = A2;
int photovalue;
int percentage_bright;
char photostring[30];

void setup() {
	Serial.begin(9600);
	pinMode(photoresistor,INPUT);
	Particle.publish("Photoresistor-status","Sensor is active");
}

void loop() {
// Wait a few seconds between measurements.
	delay(10000);
    photovalue = analogRead(photoresistor);
    percentage_bright = map(photovalue, MIN_LIGHT, MAX_LIGHT, 0, 100);

// Check if any reads failed and exit early (to try again).
	//if (isnan(photovalue)) {
		//Serial.println("Failed to read from DHT11!");
	//	Particle.publish("Light-reading", "Failed to read photo resistor!", PRIVATE);
	//}
	//else {
	    //String reading;
		//sprintf(reading.c_str(), "Humidity: %d   Temperature: %.2f");
	sprintf(photostring, "Light: %d", percentage_bright);
	Particle.publish("Photoresistor-reading", photostring, PRIVATE);
	//}
}