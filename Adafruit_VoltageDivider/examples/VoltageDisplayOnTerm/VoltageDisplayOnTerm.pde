#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_VoltageDivider.h>

/* Assign arduino pin (A0), resistor values (ohm) and a unique ID to this sensor at the same time */
Adafruit_VoltageDivider vSensor = Adafruit_VoltageDivider(A0, 54321, 30000, 7500);

void displaySensorDetails(void)
{
  sensor_t sensor;
  vSensor.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" mV");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" mV");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" mV");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void setup(void) 
{
  Serial.begin(9600);
  Serial.println("Voltage monitoring test"); Serial.println("");
  
  /* Display some basic information on this sensor */
  displaySensorDetails();
}

void loop(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  vSensor.getEvent(&event);
 
  /* Display the results*/
  Serial.print(event.Voltage); 
  Serial.println(" mV");
  delay(500);
}
