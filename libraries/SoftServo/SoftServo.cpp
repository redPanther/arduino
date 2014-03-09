
#include "SoftServo.h"

#include <avr/pgmspace.h>
#include <limits.h>
#include "pins_arduino.h"
#include "wiring_private.h"

SoftServo::SoftServo(uint8_t pin,uint32_t low_pulse, uint32_t high_pulse, uint32_t maxDelay, uint32_t mid_angle) {
  _pin = pin;
  _low_pulse  = low_pulse;
  _high_pulse = high_pulse;
  _min_angle = 0;
  _max_angle = 180;
  _angle = -1;
  _maxDelay = (maxDelay > 0) ? maxDelay : (_high_pulse - _low_pulse);
  _mid_angle = mid_angle;

  pinMode(pin,OUTPUT);
  digitalWrite(pin,LOW);
}

void SoftServo::write(uint32_t angle, int32_t servoDelay) {

  // mid correction 
  if ( _mid_angle != 90 ) {
    uint32_t mid_angle_next = _mid_angle+1;
    if ( angle > 90 ) angle = map(angle,91,_max_angle,mid_angle_next,_max_angle);
    else              angle = map(angle,_min_angle,90,_min_angle,_mid_angle);
  }
  
  angle = constrain(angle,_min_angle,_max_angle);

  // auto delay
  if ( servoDelay < 0 ) {
    if ( _angle < 0 ) {
      servoDelay = _maxDelay;
    } else {
      int32_t delta_angle = angle -_angle;
      delta_angle = abs( delta_angle );
      servoDelay = map(delta_angle,0,180,0,_maxDelay) + 50;
    }
  }

  _angle = angle;
  
  uint32_t pulsewidth = map(angle, 0, 180, _low_pulse, _high_pulse); // width in microseconds
  do {
    digitalWrite(_pin, HIGH);
    delayMicroseconds(pulsewidth);
    digitalWrite(_pin, LOW);
    delay(20); // wait for 20 milliseconds
    servoDelay -= 20;
  } while(servoDelay >=0);
}

void SoftServo::update() {
  if ( _angle > -1 )
    this->write(_angle,20);
}

uint32_t SoftServo::currentAngle() {
	return _angle;
}

void SoftServo::setMinMaxAngle(int32_t min_angle ,int32_t max_angle) {
  _min_angle = min_angle;
  _max_angle = max_angle;
}

