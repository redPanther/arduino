#include "Adafruit_VoltageDivider.h"

#include <avr/pgmspace.h>
#include <limits.h>
#include "pins_arduino.h"
#include "wiring_private.h"

Adafruit_VoltageDivider::Adafruit_VoltageDivider(uint8_t pin,int32_t sensorID, int R1, int R2,uint32_t vref ) {
  _sensorID = sensorID;
  _pin = pin;
  _R1 = R1; 
  _R2 = R2;
  _offset = 0;
  if ( vref == 0 ) {
#if defined(__AVR_ATmega32U4__) // is this a Leonardo board?
  _vref =  2560; // leo reference is 2.56 volts
#else
  _vref =  1100; // ATmega328 is 1.1 volts
#endif
    _internal_ref = true;
  } else {
    _vref = vref;
    _internal_ref = false;
  }
}

void Adafruit_VoltageDivider::getEvent(sensors_event_t *event) {
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = SENSOR_TYPE_VOLTAGE;
  event->timestamp = 0;
  

  if ( _internal_ref ) {
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega644P__)
    analogReference(INTERNAL1V1);      // set reference to internal (1.1V)
#else
    analogReference(INTERNAL);      // set reference to internal (1.1V)
#endif
    analogRead( _pin );  // allow the ADC to settle
    delay(10);

    int value = 0;
    for(int i=0; i < 8; i++) {
      value += analogRead(_pin);
    }
    value /= 8; // get the average of 8 readings
    const float DIVISOR = (float)_R2/(float)(_R1+_R2); 
    event->voltage = _offset + map(value, 0,1023, 0, (float)_vref / DIVISOR );
    analogReference(DEFAULT); // set the reference back to default (Vcc)
  } else {

    analogReference(DEFAULT); // set the reference to default (Vcc)

    int value = 0;
    for(int i=0; i < 8; i++) {
      value += analogRead(_pin);
    }
    value /= 8; // get the average of 8 readings
    event->voltage = _offset + _vref / 1023 * ( _R1 + _R2 ) / _R1 * value;
  }
  
  analogRead(_pin); // just to let the ADC settle ready for next reading
  delay(10); // allow reference to stabalise
}


void Adafruit_VoltageDivider::setOffset(int val) {
  _offset = val;
}

void Adafruit_VoltageDivider::getSensor(sensor_t *sensor) {
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  float MULTIPLIER = ( _R1 + _R2 ) / _R1;
  strncpy (sensor->name, "VoltageDivider", sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = 1;
  sensor->sensor_id   = _sensorID;
  sensor->type        = SENSOR_TYPE_VOLTAGE;
  sensor->min_delay   = 10;
  sensor->max_value   = _vref * MULTIPLIER;
  sensor->resolution  = _vref / 1023;
  sensor->min_value   = sensor->resolution * MULTIPLIER;
} 

