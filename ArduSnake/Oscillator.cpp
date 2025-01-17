//--------------------------------------------------------------
//-- Oscillator.pde
//-- Generate sinusoidal oscillations in the servos
//--------------------------------------------------------------
//-- (c) Juan Gonzalez-Gomez (Obijuan), Dec 2011
//-- GPL license
//--------------------------------------------------------------

#include "WProgram.h"
#include "Oscillator.h"
#include <Servo.h>

//-- This function returns true if another sample
//-- should be taken (i.e. the TS time has passed since
//-- the last sample was taken
bool Oscillator::next_sample()
{
  
  //-- Read current time
  _currentMillis = millis();
 
  //-- Check if the timeout has passed
  if(_currentMillis - _previousMillis > _TS) {
    _previousMillis = _currentMillis;   

    return true;
  }
  
  return false;
}

//-- Attach an oscillator to a servo
//-- Input: pin is the arduino pin were the servo
//-- is connected
void Oscillator::attach(int pin, bool rev)
{
  //-- Attach the servo and move it to the home position
  _servo.attach(pin);
  _servo.write(90);
  
  //-- Initialization of oscilaltor parameters
  _TS=30;
  _T=2000;
  _N = _T/_TS;
  _inc = 2*M_PI/_N;
  
  _previousMillis=0;
  
  //-- Default parameters
  _A=45;
  _phase=0;
  _phase0=0;
  _O=0;
  _stop=false;

  //-- Reverse mode
  _rev = rev;
}

/*************************************/
/* Set the oscillator period, in ms  */
/*************************************/
void Oscillator::SetT(unsigned int T)
{
  //-- Assign the new period
  _T=T;
  
  //-- Recalculate the parameters
  _N = _T/_TS;
  _inc = 2*M_PI/_N;
};

/*******************************************************************/
/* This function should be periodically called                     */
/* in order to maintain the oscillations. It calculates            */
/* if another sample should be taken and position the servo is so  */
/*******************************************************************/
void Oscillator::refresh()
{
  
  //-- Only When TS milliseconds have passed, the new sample is obtained
  if (next_sample()) {
  
      //-- If the oscillator is not stopped, calculate the servo position
      if (!_stop) {
        //-- Sample the sine function and set the servo pos
        _pos = round(_A * sin(_phase + _phase0) + _O);
	if (_rev) _pos=-_pos;
        _servo.write(_pos+90);

        //-- Increment the phase
        _phase = _phase + _inc;
      }  
   

  }
}


