/*
 * GccApplication2.c
 *
 * Created: 11/2/2023 6:50:14 PM
 * Author : alber
 */ 


#include "sam.h"

#define PINCFG_CONFIG_VALUE 0b0000000

int main(void)
{
	SystemInit();
	
	PORT->Group[0].PINCFG[14].reg = PINCFG_CONFIG_VALUE;
	PORT->Group[0].DIRSET.reg = PORT_PA17;
	
	PM->APBCMASK.reg |= PM_APBCMASK_TC3;
	
	GCLK->GENDIV.reg = 0x00;
	GCLK->GENCTRL.reg = 0x10600;
	GCLK->CLKCTRL.reg = 0x401B;
	
	
	TC3->COUNT16.COUNT.reg = 65307;
	TC3->COUNT16.CTRLA.reg = 0x00 | TC_CTRLA_PRESCALER_DIV1024;
	TC3->COUNT16.CTRLBSET.reg = 0x00;
	TC3->COUNT16.INTFLAG.reg = 0x01;
	
	const unsigned int CTRLA_VALUE = TC3->COUNT16.CTRLA.reg;
	TC3->COUNT16.CTRLA.reg = CTRLA_VALUE | 0x02;
	
	const unsigned int MASK = 0x80;
	
	while(1) {
		const unsigned STATUS = TC3->COUNT16.STATUS.reg;
		if((MASK & STATUS) == 0) {
			break;
		}
	}
	

    /* Replace with your application code */
    while (1) 
    {
		const unsigned int INTFLAG = TC3->COUNT16.INTFLAG.reg;
		
		if((INTFLAG & 0x01) == 0){
			continue;
		}
		
		PORT->Group[0].OUT.reg ^= PORT_PA17;
		TC3->COUNT16.INTFLAG.reg = 0x01;
		TC3->COUNT16.COUNT.reg = 65307;
    }
}
