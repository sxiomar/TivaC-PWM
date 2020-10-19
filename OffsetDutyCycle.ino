/*
 * Example for using a timer hack to create PWM on the Tiva C
 * Launchpad. The library "FullPWM" was designed to work on the 
 * TM4C123GH uController by direct register access and is not 
 * likely to work on other chips.
 * 
 */


#include "FullPWM.h"

FullPWM blue(10000, 19); //ititialize the frequency and pin. Use pin#, not label (19, not PB_2)
FullPWM red(10000, 30);

void setup() {
  delay(10);
}

void loop() {  
  for(int i = 0; i < 100; i++){
    blue.changeDuty(i); //change the duty cycle


    // create a second pwm with offset duty cycle
    if(i < 66){
      red.changeDuty(i+33);
    }else{
      red.changeDuty(i-65);
    }
    delay(50); // necessarry for o-scope triggering
  }
}
