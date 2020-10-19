#include "Energia.h"
#include "FullPWM.h"
#include <inc/tm4c123gh6pm.h>

// public constructor, once per pin and freq
FullPWM::FullPWM(int freq, int pin)
{
    pinMode(pin, OUTPUT);
    this->_pin = pin;
    this->_freq = freq;
    this->_duty = 0.01;
    this->initTimer();
}

int FullPWM::getPin(){
    int retVal = this->_pin;
    return retVal;
}

float FullPWM::getDuty(){
    float retVal = this->_duty;
    return _duty;
}

int FullPWM::getFreq(){
    int retVal = this->_freq;
    return _freq;
}

// public change the duty cycle
void FullPWM::changeDuty(float duty)
{
    _duty = duty;
    this->changeDutyHARD();
}


//This needs to be changed for each pin
void FullPWM::changeDutyHARD()
{
    int PERIOD = 80000000 / _freq;
    int INTERVAL = PERIOD - PERIOD * (_duty / 100);
    if(_pin == 19){
        TIMER3_TAMATCHR_R = INTERVAL;
    }
    if(_pin == 14){
        TIMER0_TAMATCHR_R = INTERVAL;
    }
    if(_pin == 17){
        TIMER0_TAMATCHR_R = INTERVAL;
    }
    if(_pin == 7){
        TIMER1_TAMATCHR_R = INTERVAL;
    }
    if(_pin == 40){
        TIMER1_TAMATCHR_R = INTERVAL;
    }
    if(_pin == 3){
        TIMER2_TAMATCHR_R = INTERVAL;
    }
    if(_pin == 31){
        TIMER2_TAMATCHR_R = INTERVAL;
    }
    if(_pin == 15){
        TIMER2_TBMATCHR_R = INTERVAL;
    }
    if(_pin == 30){
        TIMER0_TBMATCHR_R = INTERVAL;
    }
    if(_pin == 2){
        TIMER1_TBMATCHR_R = INTERVAL;
    }
    if(_pin == 39){
        TIMER1_TBMATCHR_R = INTERVAL;
    }
    if(_pin == 4){
        TIMER2_TBMATCHR_R = INTERVAL;
    }
    if(_pin == 38){
        TIMER3_TBMATCHR_R = INTERVAL;
    }
}

/******************************************************************************


    The following methods are basically the same but need to be repeated for each pin as
    by register address.

    1) select timer - eg. 0, 1, 2 . . . 5
    2) disable the timer for configuration
    3) set to 16 bit mode (rather than 32)
    4) set periodic, match value
    5) & 6) set preloader
    7) set interval
    8) re enable timer - config is done
    9) wire to the pin for output

******************************************************************************/
void FullPWM::initTimer()
{
    int PERIOD = 80000000 / _freq;
    int INTERVAL = PERIOD - PERIOD * (_duty / 100);
    //int INTERVAL = 2000;

    if (_pin == 19)
    {
        SYSCTL_RCGCTIMER_R |= 0x08;
        TIMER3_CTL_R &= ~TIMER_CTL_TAEN;
        TIMER3_CFG_R = TIMER_CFG_16_BIT;
        TIMER3_TAMR_R = 0b1010;
        TIMER3_TAILR_R = PERIOD & 0xffff;
        TIMER3_TAPR_R = PERIOD >> 16;
        TIMER3_TAMATCHR_R = INTERVAL;
        TIMER3_CTL_R |= TIMER_CTL_TAEN;
        GPIO_PORTB_AFSEL_R |= 0x04;
        GPIO_PORTB_PCTL_R = 0x00000700;
    }
    
    //--------------------------------------------------------------------------PB_6
    if (_pin == 14)
    {
        SYSCTL_RCGCTIMER_R |= 0x01;
        TIMER0_CTL_R &= ~TIMER_CTL_TAEN;
        TIMER0_CFG_R = TIMER_CFG_16_BIT;
        TIMER0_TAMR_R = 0b1010;
        TIMER0_TAILR_R = PERIOD & 0xffff;
        TIMER0_TAPR_R = PERIOD >> 16;
        TIMER0_TAMATCHR_R = INTERVAL;
        TIMER0_CTL_R |= TIMER_CTL_TAEN;
        GPIO_PORTB_AFSEL_R |= 0x40;
        GPIO_PORTB_PCTL_R = 0x07000000;
    }
    //--------------------------------------------------------------------------PF_0
    if (_pin == 17)
    {
        SYSCTL_RCGCTIMER_R |= 0x01;
        TIMER0_CTL_R &= ~TIMER_CTL_TAEN;
        TIMER0_CFG_R = TIMER_CFG_16_BIT;
        TIMER0_TAMR_R = 0b1010;
        TIMER0_TAILR_R = PERIOD & 0xffff;
        TIMER0_TAPR_R = PERIOD >> 16;
        TIMER0_TAMATCHR_R = INTERVAL;
        TIMER0_CTL_R |= TIMER_CTL_TAEN;
        GPIO_PORTF_AFSEL_R |= 0x01;
        GPIO_PORTF_PCTL_R = 0x00000007;
    }

    //--------------------------------------------------------------------------PB_4
    if (_pin == 7)
    {
        SYSCTL_RCGCTIMER_R |= 0x02;
        TIMER1_CTL_R &= ~TIMER_CTL_TAEN;
        TIMER1_CFG_R = TIMER_CFG_16_BIT;
        TIMER1_TAMR_R = 0b1010;
        TIMER1_TAILR_R = PERIOD & 0xffff;
        TIMER1_TAPR_R = PERIOD >> 16;
        TIMER1_TAMATCHR_R = INTERVAL;
        TIMER1_CTL_R |= TIMER_CTL_TAEN;
        GPIO_PORTB_AFSEL_R |= 0x10;
        GPIO_PORTB_PCTL_R = 0x00070000;
    }
    //--------------------------------------------------------------------------PF_2
    if (_pin == 40)
    {
        SYSCTL_RCGCTIMER_R |= 0x02;
        TIMER1_CTL_R &= ~TIMER_CTL_TAEN;
        TIMER1_CFG_R = TIMER_CFG_16_BIT;
        TIMER1_TAMR_R = 0b1010;
        TIMER1_TAILR_R = PERIOD & 0xffff;
        TIMER1_TAPR_R = PERIOD >> 16;
        TIMER1_TAMATCHR_R = INTERVAL;
        TIMER1_CTL_R |= TIMER_CTL_TAEN;
        GPIO_PORTF_AFSEL_R |= 0x04;
        GPIO_PORTF_PCTL_R = 0x00000700;
    }
    //--------------------------------------------------------------------------PB_0
    if (_pin == 3)
    {
        SYSCTL_RCGCTIMER_R |= 0x04;
        TIMER2_CTL_R &= ~TIMER_CTL_TAEN;
        TIMER2_CFG_R = TIMER_CFG_16_BIT;
        TIMER2_TAMR_R = 0b1010;
        TIMER2_TAILR_R = PERIOD & 0xffff;
        TIMER2_TAPR_R = PERIOD >> 16;
        TIMER2_TAMATCHR_R = INTERVAL;
        TIMER2_CTL_R |= TIMER_CTL_TAEN;
        GPIO_PORTB_AFSEL_R |= 0x40;
        GPIO_PORTB_PCTL_R = 0x00000007;
    }
    //--------------------------------------------------------------------------PF_4
    if (_pin == 31)
    {
        SYSCTL_RCGCTIMER_R |= 0x04;
        TIMER2_CTL_R &= ~TIMER_CTL_TAEN;
        TIMER2_CFG_R = TIMER_CFG_16_BIT;
        TIMER2_TAMR_R = 0b1010;
        TIMER2_TAILR_R = PERIOD & 0xffff;
        TIMER2_TAPR_R = PERIOD >> 16;
        TIMER2_TAMATCHR_R = INTERVAL;
        TIMER2_CTL_R |= TIMER_CTL_TAEN;
        GPIO_PORTF_AFSEL_R |= 0x10;
        GPIO_PORTF_PCTL_R = 0x00070000;
    }
    
    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------Timer B section
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------PB_7
    if (_pin == 15)
    {
        SYSCTL_RCGCTIMER_R |= 0x01;
        TIMER0_CTL_R &= ~TIMER_CTL_TBEN;
        TIMER0_CFG_R = TIMER_CFG_16_BIT;
        TIMER0_TBMR_R = 0b1010;
        TIMER0_TBILR_R = PERIOD & 0xffff;
        TIMER0_TBPR_R = PERIOD >> 16;
        TIMER0_TBMATCHR_R = INTERVAL;
        TIMER0_CTL_R |= TIMER_CTL_TBEN;
        GPIO_PORTB_AFSEL_R |= 0x80;
        GPIO_PORTB_PCTL_R = 0x70000000;
    }
    //--------------------------------------------------------------------------PF_1
    if (_pin == 30)
    {
        SYSCTL_RCGCTIMER_R |= 0x01;
        TIMER0_CTL_R &= ~TIMER_CTL_TBEN;
        TIMER0_CFG_R = TIMER_CFG_16_BIT;
        TIMER0_TBMR_R = 0b1010;
        TIMER0_TBILR_R = PERIOD & 0xffff;
        TIMER0_TBPR_R = PERIOD >> 16;
        TIMER0_TBMATCHR_R = INTERVAL;
        TIMER0_CTL_R |= TIMER_CTL_TBEN;
        GPIO_PORTF_AFSEL_R |= 0x02;
        GPIO_PORTF_PCTL_R = 0x00000070;
    }
    //--------------------------------------------------------------------------PB_5
    if (_pin == 2)
    {
        SYSCTL_RCGCTIMER_R |= 0x02;
        TIMER1_CTL_R &= ~TIMER_CTL_TBEN;
        TIMER1_CFG_R = TIMER_CFG_16_BIT;
        TIMER1_TBMR_R = 0b1010;
        TIMER1_TBILR_R = PERIOD & 0xffff;
        TIMER1_TBPR_R = PERIOD >> 16;
        TIMER1_TBMATCHR_R = INTERVAL;
        TIMER1_CTL_R |= TIMER_CTL_TBEN;
        GPIO_PORTB_AFSEL_R |= 0x20;
        GPIO_PORTB_PCTL_R = 0x00700000;
    }
    //--------------------------------------------------------------------------PF_3
    if (_pin == 39)
    {
        SYSCTL_RCGCTIMER_R |= 0x02;
        TIMER1_CTL_R &= ~TIMER_CTL_TBEN;
        TIMER1_CFG_R = TIMER_CFG_16_BIT;
        TIMER1_TBMR_R = 0b1010;
        TIMER1_TBILR_R = PERIOD & 0xffff;
        TIMER1_TBPR_R = PERIOD >> 16;
        TIMER1_TBMATCHR_R = INTERVAL;
        TIMER1_CTL_R |= TIMER_CTL_TBEN;
        GPIO_PORTF_AFSEL_R |= 0x08;
        GPIO_PORTF_PCTL_R = 0x00007000;
    }
    //--------------------------------------------------------------------------PB_1
    if (_pin == 4)
    {
        SYSCTL_RCGCTIMER_R |= 0x04;
        TIMER2_CTL_R &= ~TIMER_CTL_TBEN;
        TIMER2_CFG_R = TIMER_CFG_16_BIT;
        TIMER2_TBMR_R = 0b1010;
        TIMER2_TBILR_R = PERIOD & 0xffff;
        TIMER2_TBPR_R = PERIOD >> 16;
        TIMER2_TBMATCHR_R = INTERVAL;
        TIMER2_CTL_R |= TIMER_CTL_TBEN;
        GPIO_PORTB_AFSEL_R |= 0x02;
        GPIO_PORTB_PCTL_R = 0x00000070;
    }
    //--------------------------------------------------------------------------PB_3
    if (_pin == 38)
    {
        SYSCTL_RCGCTIMER_R |= 0x08;
        TIMER3_CTL_R &= ~TIMER_CTL_TBEN;
        TIMER3_CFG_R = TIMER_CFG_16_BIT;
        TIMER3_TBMR_R = 0b1010;
        TIMER3_TBILR_R = PERIOD & 0xffff;
        TIMER3_TBPR_R = PERIOD >> 16;
        TIMER3_TBMATCHR_R = INTERVAL;
        TIMER3_CTL_R |= TIMER_CTL_TBEN;
        GPIO_PORTB_AFSEL_R |= 0x08;
        GPIO_PORTB_PCTL_R = 0x00007000;
    }
    
}