// uLCD-144-G2 basic text demo program for uLCD-4GL LCD driver library
//
#include "mbed.h"
#include "uLCD_4DGL.h"

DigitalIn bup(D6);
DigitalIn bdn(D8);
DigitalIn bst(D5);

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;

AnalogOut aout(PA_4);
AnalogIn Ain(A0);

int sample = 100;
float ADCdata[240];
float f = 1.0;
int h = 0;
float x = 1.0;
int coun=1;
float T=1.0/f;
int k = 0;
float p = 1.0;
int c =1;

void button()
{
  switch(coun%4)
    {
      case 1:
        uLCD.printf("\n 1/8 \n");
        x = 0.125;
        break;
      case 2:
        uLCD.printf("\n 1/4 \n");
        x = 0.25;
        break;
      case 3:
        uLCD.printf("\n 1/2 \n");
        x = 0.5;
        break;
      case 0:
        x = 1.0;
        uLCD.printf("\n 1 \n");
        break;
    }
}
int main()
{
  while(1){
    if(bup == 1){  
      coun++;
      button();
    }else if(bdn == 1){       
      if (coun == 0) coun = 0;
  	  else coun--;
      button();
    }
    if(bst == 1){
      f= x;
      printf("%d\r\n",(int)(f*10));
      break;
    }
  }


//      thread.start(analy);

	for (h = 0; h < 10; h++) {
		for (float i = 0.0; i < 0.91; i += 0.91/(m-1)) {
		  aout = i;
      p = aout;
      //c++;
      //printf("c=%d",c);
		//printf("aout = %f volts\n", aout.read() * 3.3f);
		  wait_us(0.001*1000000);
		}
    for (float i = 0.0f; i < 0.91f; i += 0.91/(m-1)) {
		  aout = p;
		//printf("aout = %f volts\n", aout.read() * 3.3f);
		  wait_us(0.001*1000000);
		}
		for (float i = 0.91f; i > 0.0f; i -= 0.91/(m-1)) {
		  aout = i;
		  wait_us(0.001*1000000);
		}
	}

	for (h = 0; h < 2; h++) {
		for (float i = 0.0f; i < 0.91f; i += 0.91/(m-1)) {
			aout = i;
      p = aout;
			ADCdata[k++] = Ain;
			//printf("aout = %f volts\n", aout.read() * 3.3f);
			wait_us(0.001*1000000);
		}
    for (float i = 0.0f; i < 0.91f; i += 0.91/(m-1)) {
		  aout = p;
      ADCdata[k++] = Ain;
		//printf("aout = %f volts\n", aout.read() * 3.3f);
		  wait_us(0.001*1000000);
		}
		for (float i = 0.91f; i > 0.0f; i -= 0.91/(m-1)) {
			aout = i;
			ADCdata[k++] = Ain;
			//printf("aout = %f volts\n", aout.read() * 3.3f);
			wait_us(0.001*1000000);
		}
	}

    for (k = 0; k < 240; k++){
      printf("%f\r\n", ADCdata[k]);
    }
}
