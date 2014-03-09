#include "Adafruit_Ultrasonic.h"

#include <avr/pgmspace.h>
#include <limits.h>
#include "pins_arduino.h"
#include "wiring_private.h"

Adafruit_Ultrasonic::Adafruit_Ultrasonic(uint8_t pin,int32_t sensorID) {
  _sensorID = sensorID;
  _pin = pin;
}

void Adafruit_Ultrasonic::getEvent(sensors_event_t *event) {
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = SENSOR_TYPE_PROXIMITY;
  event->timestamp = 0;

  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  delayMicroseconds(2);

  digitalWrite(_pin, HIGH);
  delayMicroseconds(5);

  digitalWrite(_pin,LOW);
  pinMode(_pin,INPUT);
 
  long duration =  pulseIn(_pin,HIGH,20000);  // if a pulse does not arrive in 20 ms then the ping sensor is not connected

  if(duration >=20000)
    duration = 10000;
  
  event->distance = duration / 29.0 / 2.0;
}

void Adafruit_Ultrasonic::getSensor(sensor_t *sensor) {
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, "Ultrasonic", sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = 1;
  sensor->sensor_id   = _sensorID;
  sensor->type        = SENSOR_TYPE_PROXIMITY;
  sensor->min_delay   = 0;
  sensor->max_value   = 0;               
  sensor->min_value   = 400;
  sensor->resolution  = 1;                
} 
