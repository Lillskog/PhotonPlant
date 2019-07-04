int soilMoisturePin = A0;
int AirValue = 520;
int WaterValue = 260;
int interval = (AirValue - WaterValue)/3;
int soilMoistureValue = 0;
int soilNormalized = 0;

void setup() {
    pinMode(soilMoisturePin, INPUT);
    Serial.begin(9600);
}

void loop() {
    soilMoistureValue = analogRead(soilMoisturePin);
    //soilNormalized = normalize(soilMoistureValue);
    
    if (soilMoistureValue > WaterValue && soilMoistureValue < (WaterValue + interval)) {
        //Serial.printf('Soil is very wet! Dryness %i %', soilNormalized);
        Particle.publish("soil-status","Soil is very wet",PRIVATE);
    }
        
    else if (soilMoistureValue > (WaterValue + interval) && soilMoistureValue < (AirValue - interval)) {
        //Serial.printf('Soil is wet! Dryness %i %', soilNormalized);
        Particle.publish("soil-status","Soil is wet",PRIVATE);
    }
    
    else if (soilMoistureValue > (AirValue - interval) && soilMoistureValue < AirValue) {
        //Serial.printf('Soil is dry! Dryness %i %', soilNormalized);
        Particle.publish("soil-status","Soil is dry",PRIVATE);
    }
    
    delay(1000);
}

int normalize(int Value) {
    return (Value - WaterValue)/(AirValue - WaterValue)*100;
}