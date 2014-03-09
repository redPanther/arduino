#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_Ultrasonic.h>

/* Assign arduino pin (A0), resistor values (ohm) and a unique ID to this sensor at the same time */
Adafruit_Ultrasonic sonar(8, 54321);

void displaySensorDetails(void)
{
  sensor_t sensor;
  sonar.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" cm");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" cm");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" cm");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void setup(void) 
{
  Serial.begin(9600);
  Serial.println("Ultrasonic Ranger test"); Serial.println("");
  
  /* Display some basic information on this sensor */
  displaySensorDetails();
}

void loop(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  sonar.getEvent(&event);
 
  /* Display the results*/
  Serial.print(event.distance); 
  Serial.println(" cm");
  delay(500);
}