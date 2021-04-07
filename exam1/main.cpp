// uLCD-144-G2 basic text demo program for uLCD-4GL LCD driver library
//
#include "mbed.h"
#include "uLCD_4DGL.h"

DigitalIn bup(D6);
DigitalIn bdn(D8);
DigitalIn bst(D5);
//DigitalIn bup(D10);
//DigitalIn bdn(D3);
//DigitalIn bst(D5);
//DigitalOut led(LED3);
uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;

AnalogOut aout(PA_4);
AnalogIn Ain(A0);
//AnalogIn Ain(D6);

int sample = 100;
float ADCdata[240];
float f = 1.0;
int h = 0;
float x = 1.0;
int coun=501;
float T=1.0/f;
int k = 0;
float p=1.0;

void button()
{
  switch(coun%6)
    {
      case 1:
        uLCD.locate(0,0);
        uLCD.color(RED);
        uLCD.printf("\n 1/8 \n");
        uLCD.color(GREEN);
        uLCD.printf("\n 1/4 \n");
        uLCD.printf("\n 1/2 \n");
        uLCD.printf("\n 1   \n");

        x = 10;
        break;
      case 2:
        uLCD.locate(0,0);
        uLCD.color(GREEN);
        uLCD.printf("\n 1/8 \n");
        uLCD.color(RED);
        uLCD.printf("\n 1/4 \n");
        uLCD.color(GREEN);
        uLCD.printf("\n 1/2 \n");
        uLCD.printf("\n 1   \n");

        x = 20;
        break;
      case 3:
        uLCD.locate(0,0);
        uLCD.color(GREEN);
        uLCD.printf("\n 1/8 \n");
        uLCD.printf("\n 1/4 \n");
        uLCD.color(RED);
        uLCD.printf("\n 1/2 \n");
        uLCD.color(GREEN);
        uLCD.printf("\n 1   \n");
        x = 40;
        break;
      case 4:
        uLCD.locate(0,0);
        uLCD.color(GREEN);
        uLCD.printf("\n 1/8 \n");
        uLCD.printf("\n 1/4 \n");
        uLCD.printf("\n 1/2 \n");
        uLCD.color(RED);
        uLCD.printf("\n 1   \n");

        x = 80;
        break;
    }
}
int main()
{
  while(1){
    if(bup == 1){  
      coun++;
 //     led = !led;
      button();
    }else if(bdn == 1){       
      if (coun == 0) coun = 0;
	  else coun--;

      button();
    }
    if(bst == 1){
      f= x;
     // printf("%d\r\n",(int)(f*10));
      break;
    }
  }


//      thread.start(analy);

	for (h = 0; h < 10; h++) {
		for (float i = 0.0f; i < 0.91f; i += 0.91/(f-1)) {
		aout = i;
        p = aout;
		//printf("aout = %f volts\n", aout.read() * 3.3f);
		wait_us(0.001*1000000);
		}
        for (float i = 0.0f; i < 0.91f; i += 0.91/(f-1)) {
		  aout = p;
		//printf("aout = %f volts\n", aout.read() * 3.3f);
		  wait_us(0.001*1000000);
		}
		for (float i = 0.91f; i > 0.0f; i -= 0.91/(f-1)) {
		aout = i;
		//printf("aout = %f volts\n", aout.read() * 3.3f);
		wait_us(0.001*1000000);
		}
	}

	for (h = 0; h < 2; h++) {
		for (float i = 0.0f; i < 0.91f; i += 0.91/(f-1)) {
			aout = i;
			ADCdata[k++] = Ain;
			//printf("aout = %f volts\n", aout.read() * 3.3f);
			wait_us(0.001*1000000);
		}
        for (float i = 0.0f; i < 0.91f; i += 0.91/(f-1)) {
		  aout = p;
          ADCdata[k++] = Ain;
		//printf("aout = %f volts\n", aout.read() * 3.3f);
		  wait_us(0.001*1000000);
		}
		for (float i = 0.91f; i > 0.0f; i -= 0.91/(f-1)) {
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
