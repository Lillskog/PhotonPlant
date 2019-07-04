// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_DHT.h>
#include <Particle.h>

// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#define DHTPIN 6
#define DHTTYPE DHT11		// DHT 11 

char temphumstring[30];

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT dht(DHTPIN, DHTTYPE);

void setup() {
	Serial.begin(9600); 
	//Serial.println("DHTxx test!");
	Particle.publish("DHT11-status","Sensor is active");
	dht.begin();
}

void loop() {
// Wait a few seconds between measurements.
	delay(2000);
    
// Reading temperature or humidity takes about 250 milliseconds!
// Sensor readings may also be up to 2 seconds 'old' (its a 
// very slow sensor)
	float h = dht.getHumidity();
// Read temperature as Celsius
	float t = dht.getTempCelcius();
// Read temperature as Farenheit
//	float f = dht.getTempFarenheit();

// Check if any reads failed and exit early (to try again).
	if (isnan(h) || isnan(t)) {
		//Serial.println("Failed to read from DHT11!");
		Particle.publish("DHT11-reading", "Failed to read DHT11!", PRIVATE);
	}
	else {
	    //String reading;
		//sprintf(reading.c_str(), "Humidity: %d   Temperature: %.2f");
		sprintf(temphumstring,"Humidity: %f%    Temperature: %.2f°C", h, t);
		Particle.publish("DHT11-reading", String(t), PRIVATE);
	}

// Compute heat index
// Must send in temp in Fahrenheit!
//	float hi = dht.getHeatIndex();
//	float dp = dht.getDewPoint();
//	float k = dht.getTempKelvin();
//	Serial.println(Time.timeStr());
}