#include "hal_utilities.h"

void delay_us(u32 nus)
{
    OS_ERR os_err;
    
    u32 fac_us   = 16;//128/8 systickΪ8��Ƶ, 1us��Ҫ��������Ϊ10^-6��[1/(SystemCoreClock/8)]=SystemCoreClock/8000000
	u32 ticks    = 0;
	u32 told     = 0,tnow = 0,tcnt = 0;
	u32 reload = SysTick->LOAD;	  
    
	ticks = nus*fac_us;
    
	OSSchedLock(&os_err);				
	told = SysTick->VAL;        	
	while (1) {
		tnow = SysTick->VAL;
        
		if (tnow != told) {	  
            tcnt += (tnow < told)?((told - tnow)):((reload - tnow + told));
			told = tnow;
            
			if(tcnt >= ticks) {
                break;
            }
		}  
	}
	OSSchedUnlock(&os_err);	
}