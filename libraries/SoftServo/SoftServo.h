/*
  Adafruit_Ultrasonic.h - Ultrasonic driver Library based on Adafruit unified sensor driver system.
  
  tested with seeed studio ultrasonic ranger
    
  ported to AF sensor system by SM
  
  2011 Copyright (c) Seeed Technology Inc.  All right reserved.
  For Ultrasonic v1.0 firmware.
 
  Original Author: LG
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _SOFT_SERVO_H_
#define _SOFT_SERVO_H_

#if ARDUINO >= 100
 #include "Arduino.h"
 #include "Print.h"
#else
 #include "WProgram.h"
#endif

class SoftServo {

 public: 
  /* Constructor */
  SoftServo(uint8_t,uint32_t low_pulse=600, uint32_t high_pulse=2400, uint32_t maxDelay=0, uint32_t mid_angle=90);

  void write(uint32_t angle,int32_t servoDelay=-1);
  void update();
  uint32_t currentAngle();
  void setMinMaxAngle(int32_t ,int32_t );
 private:
   int32_t _low_pulse;
   int32_t _high_pulse;
   int32_t _angle;
   int32_t _maxDelay;
   int32_t _min_angle;
   int32_t _max_angle;
   uint32_t _mid_angle;
   uint8_t _pin;
};

#endif
