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

#ifndef _ADAFRUIT_SENSOR_VOLTAGE_DIVIDER_
#define _ADAFRUIT_SENSOR_VOLTAGE_DIVIDER_

#if ARDUINO >= 100
 #include "Arduino.h"
 #include "Print.h"
#else
 #include "WProgram.h"
#endif

#include <Adafruit_Sensor.h>

class Adafruit_VoltageDivider : public Adafruit_Sensor {

 public: 
  /* Constructor */
  Adafruit_VoltageDivider(uint8_t,int32_t,int,int,uint32_t vref=0 );

  void setOffset(int);
  void getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  
 private:
   int32_t _sensorID;
   uint8_t _pin;
   uint32_t _vref;
   int _R1;
   int _R2;
	int _offset;
   bool _internal_ref;
	
};

#endif
