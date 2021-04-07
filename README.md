# exam
# exam
*按鈕
```C++
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
```

int main()
{
*按鈕選擇
```C++
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
     // printf("%d\r\n",(int)(f*10));
      break;
    }
  }
```
* 產生波
>橫軸分240等分
>>依SLEW不同，3區塊分不同等分
>>EX:若SLEW=1，分三等份，每一等分80小格，要上升79次
```C++
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
```
*存sample值
```C++
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
```
#FFT
* 將波型和FFT印在同張圖
```
import matplotlib.pyplot as plt
import numpy as np
import serial
import time

Fs = 128.0;  # sampling rate
Ts = 1.0/Fs; # sampling interval
t = np.arange(0,1,Ts) # time vector; create Fs samples between 0 and 1.0 sec.
y = np.arange(0,1,Ts) # signal vector; create Fs samples

n = len(y) # length of the signal
k = np.arange(n)
T = n/Fs
frq = k/T # a vector of frequencies; two sides frequency range
frq = frq[range(int(n/2))] # one side frequency range

serdev = '/dev/ttyACM0'
s = serial.Serial(serdev)
for x in range(0, int(Fs)):
    line=s.readline() # Read an echo string from B_L4S5I_IOT01A terminated with '\n'
    # print line
    y[x] = float(line)

Y = np.fft.fft(y)/n*2 # fft computing and normalization
Y = Y[range(int(n/2))] # remove the conjugate frequency parts

fig, ax = plt.subplots(2, 1)
ax[0].plot(t,y)
ax[0].set_xlabel('Time')
ax[0].set_ylabel('Amplitude')
ax[1].plot(frq,abs(Y),'r') # plotting the spectrum
ax[1].set_xlabel('Freq (Hz)')
ax[1].set_ylabel('|Y(freq)|')
plt.show()
s.close()
```
結果
1/2
![image](https://user-images.githubusercontent.com/79571560/113850641-42d0c480-97cd-11eb-911b-a17291b62fe5.png)
![image](https://user-images.githubusercontent.com/79571560/113850666-49f7d280-97cd-11eb-8b30-d6ce34ee234d.png)

1
![image](https://user-images.githubusercontent.com/79571560/113850752-5ed46600-97cd-11eb-8825-48574ce6a675.png)
![image](https://user-images.githubusercontent.com/79571560/113850780-66940a80-97cd-11eb-9d3f-facf1d3934db.png)

1/8
![image](https://user-images.githubusercontent.com/79571560/113850860-7a3f7100-97cd-11eb-8338-6a832901eec4.png)
![image](https://user-images.githubusercontent.com/79571560/113850912-84fa0600-97cd-11eb-9701-77fdf8e5fd28.png)

1/4
![image](https://user-images.githubusercontent.com/79571560/113850943-8cb9aa80-97cd-11eb-85ca-49987ef9e75a.png)
![image](https://user-images.githubusercontent.com/79571560/113850980-96dba900-97cd-11eb-9ea6-c6967fab9613.png)








