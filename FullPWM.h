/*
Purpose: PWM for Tiva C (TM4C123GH6PM)
By     : Silas Delistovic
Date   : 10/14/2020

Totally free and open source, un-owned code
*/


#ifndef FullPWM_h
#define FullPWM_h

#include "Energia.h"
#include <inc/tm4c123gh6pm.h>

class FullPWM
{
public:
  FullPWM(int freq, int pin);
  void changeDuty(float duty);
  int getPin();
  float getDuty();
  int getFreq(); 
private:
  void initTimer();
  void changeDutyHARD();
  int _pin;
  float _duty;
  int _freq;
};

#endif