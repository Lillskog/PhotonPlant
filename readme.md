# PhotonPlant

## Sensors
### Temperature & humidity sensor (DHT11)
![DHT11 Pins](https://www.maxphi.com/wp-content/uploads/2017/08/dht11-pinout-173x300.png)
[DHT11 Datasheet](https://www.mouser.com/ds/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf)

The datasheet recommends a 5k pull-up resistor from the data pin. Note! The performance of this particular sensor is questionable... for more solid readings try the DHT22.

### Soil moisture sensor (SEN0193)
[SEN0193 Datasheet](https://media.digikey.com/pdf/Data%20Sheets/DFRobot%20PDFs/SEN0193_Web.pdf)

This sensor allows analog readings of the soil moisture levels. To define the boundaries it is exposed to both water(wet) and air(dry), documenting the analog readings of the respective case. For convenient interpretation, this range is normalized to 0(dry)-100(wet)%. Note! The pre-defined boundaries are a product of a 5V power supply. 

### Photo resistor
The photo resistor used is nothing fancy (for more advance sensors look into breakout boards measuring light/UV). Various projects recommends a 10k pull-down resistor. The boundaries dark/bright are defined by blocking the sensor/exposing it to a flashlight. Note! The pre-defined boundaries are a product of a 5V power supply. 

## Schematics

## Task log
- [x] Setting up Particle Photon (2019-07-03)
- [x] Individual functionality for each sensor (2019-07-04)
- [ ] Merge and read all sensors at once
- [ ] Prototyping
- [ ] Add functionality to control water pump using a relay
- [ ] Define the sweet spots 
- [ ] Implement machine learning algorithm to process data and optimize plant growth
