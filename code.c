#include "stm32f10x.h"
volatile int sayac;
volatile int asama;
void SysTick_Handler(void)
	{
		sayac++;
	}
int main()
{
	RCC -> APB2ENR |= (1<<4);
	GPIOC -> CRH &=~((1<<26)|(1<<25)|(1<<24));
	GPIOC -> CRH |=(1<<27);
	
	GPIOC -> CRH |=((1<<20)|(1<<21));
	GPIOC -> CRH &=~((1<<22)|(1<<23));
	SysTick->LOAD=(72000000/8000);
	sayac=0;
	asama=0;
	while(1){
		
		while(!(GPIOC->IDR&(1<<14))){for(int i=0;i<50;i++);}
		while(GPIOC->IDR&(1<<14)){for(int i=0;i<50;i++);}
		if(!(GPIOC->IDR&(1<<14)))
		{ 
			if(asama==0) {
			sayac=0;
			SysTick->CTRL=3;
			asama=1;
			}
			else 
				{if((sayac>0) && (sayac<=1000)){
				GPIOC->ODR |=(1<<13);
				for(int i=0;i<2000000;i++);
				GPIOC->ODR &=~(1<<13);
				for(int i=0;i<2000000;i++);
			}
				asama=0;
				SysTick->CTRL=0;
				sayac=0;
				
			}
		}
		

		
	}
}

