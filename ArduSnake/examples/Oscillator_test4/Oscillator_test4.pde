//--------------------------------------------------------------
//-- ArduSnake library: Locomotion of modular snake robots
//-----------------------------------------------------------
//-- Layer: Oscillator
//------------------------------------------------------------
//-- Example of use of the Oscillator layer
//--
//-- Example 4: Two servos oscillating with the same parameters,
//--   excepts the phase. There is a phase difference between the
//--   two oscillators, so that a mini-wave appears
//--------------------------------------------------------------
//-- (c) Juan Gonzalez-Gomez (Obijuan), Feb-2012
//-- GPL license
//--------------------------------------------------------------
#include <Servo.h>
#include <Oscillator.h>
#include "skymega.h"

//-- Declare two oscillators
Oscillator osc[2];

//-- Global parameters for the oscillators
//-- Change this parameters for generating different mini-waves
const int A=40;
const int O=40;
const int T=2000;
const double phase_diff = DEG2RAD(-45);

void setup()
{
  //-- Attach the oscillators to the two servos
  //-- SERVO 2 and SERVO 4 for the skymega
  //-- If using arduino, you can use the pin numbers (8 and 9 for example)
  osc[0].attach(SERVO2);
  osc[1].attach(SERVO4);

  //-- Configure the oscillators with the same parameters
  for (int i=0; i<2; i++) {
    osc[i].SetO(O);
    osc[i].SetA(A);
    osc[i].SetT(T);
  }

  //-- Set the phase difference
  osc[0].SetPh(0);
  osc[1].SetPh(phase_diff);

}

void loop()
{
  //-- Refresh the oscillators
  for (int i=0; i<2; i++)
    osc[i].refresh();
}


