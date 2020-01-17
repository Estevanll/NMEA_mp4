#include <stdio.h>
#include "gpio.h"
#include "bubblesort.h"
#include "leon3.h"

#include <stdio.h>
#include <stdlib.h>

#define CALC 6
#define FIN 7
#define ERR 8


volatile uint8_t c0Running = 1;
volatile uint8_t c1Running = 1;
volatile uint8_t c2Running = 1;
volatile uint8_t c3Running = 1;
volatile uint32_t C0total = 0;
volatile uint32_t C1total = 0;
volatile uint32_t C2total = 0;
volatile uint32_t C3total = 0;
uint8_t bsArray0[BSIZE];

int checksum(const char*);

int checksum(const char *s) {
	int c = 0;

	while(*s)
		c ^= *s++;

	return c;
}

volatile int i=0;
//correct checksum = 0x76 = 118 decimal
const char *nmeamsg = "GPGGA,092750.000,5321.6802,N,00630.3372,W,1,8,1.03,61.7,M,55.2,M,,";

int main(void) {
	if(get_proc_index() == 0){//CPU0

		int chks;
		int x =0;

		start_processor(1);//start CPU1

		for(x=0;x<=1000;x++){

		}	


		GPIO_SET_OUTPUTS;
		GPIO_WRITE(0x0);
		c0Running = 1;
		while(i<IRUNS){
			GPIO_SETPIN(CALC);
			chks=checksum(nmeamsg);

			if(chks!=118) {
				GPIO_SETPIN(ERR);
			}

			GPIO_WRITE(0x0);
			i++;
		}
		GPIO_SETPIN(FIN);
		c0Running = 0;

	} //fin CPU0

	else if(get_proc_index() == 1){ 
		uint8_t bsArray1[BSIZE];
		c1Running = 1;

		C1total = 0;
		do{
			fillArray(bsArray1);
			bubblesort(bsArray1);
			C1total++;
		}while(c1Running == 1);

	}
	else if(get_proc_index() == 2){
		uint8_t bsArray2[BSIZE];
		c2Running = 1;

		C2total = 0;
		do{
			fillArray(bsArray2);
			bubblesort(bsArray2);
			C2total++;
		}while(c2Running == 1);

	}
	else if(get_proc_index() == 3){
		uint8_t bsArray3[BSIZE];
		c3Running = 1;

		C3total = 0;
		do{
			fillArray(bsArray3);
			bubblesort(bsArray3);
			C3total++;
		}while(c3Running == 1);
	}
return 0;

}
