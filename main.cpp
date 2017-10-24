#include "mbed.h"

Timer t;
DigitalIn echo(D8); //HC-SR04
DigitalOut trig(D9); //HC-SR04
DigitalOut LED(D7); //open LED
DigitalOut faucet(D6); //give water
DigitalOut multiPin0(D10); //HEF4067BP 16-channel analog multiplexer/demultiplexer A0
DigitalOut multiPin1(D11); //HEF4067BP 16-channel analog multiplexer/demultiplexer A1
DigitalOut multiPin2(D12); //HEF4067BP 16-channel analog multiplexer/demultiplexer A2
DigitalOut multiPin3(D13); //HEF4067BP 16-channel analog multiplexer/demultiplexer A3

AnalogIn readLight(A0); //Read photoresistance value

//
//bool containerFound2();
//light sensor height in CM, index 0 to 14 is count from real world up to bottom
float lightValueHeight[15]= {15.3, 14.3, 13.4, 12.3, 11.3, 10.2, 9.2, 8.2, 7.2, 6.2, 5.2, 4.2, 3.1, 2.1, 0.9};
//light sensor read value, index 0 to 14 is count from real world bottom to up
float lightValue[15];
//light sensor value difference, index 0 to 13 is count from real world bottom to up
float diffBTWlightValue[14];
//the trigger value of light sensor value difference to determine cup height
float triggerLightStrength = 0.15;
//the max height of giving water
float maxHeight;
//HCSR to the ground
float HCSRHeight=18.8;//(cm)
//ground height
float groundHeight=0.28;//real=0.267
//determine fill or not, how many time touch the target level will be recognize to finish
int tolerateError=5;
//
float containerBot=0;

//get water level directly from HC-SR04
float getDepth_real()
{
    trig = 1;
    wait(0.00001); // 10 us TTL wave
    trig = 0;
    while(echo.read()!=1) {}
    t.start();
    while(echo.read()!=0) {}
    t.stop();
    float val;
    if(t.read()<0.06f)val=t.read()*17160;
    wait(0.01);
    t.reset();
    return val;
}

//processing the getDepth_real data
float getDepth_waterlevel()
{
    float waterlevel=HCSRHeight-getDepth_real();
    return waterlevel;
}

//read light from HEF4067BP from 15 photoresistances
//from Y0 to Y14 is real world bottom to up
float readLightFromMulti(int num)
{
    if(num<0)num=0;
    if(num>14)num=14;
    multiPin0=num%2;
    num=num/2;
    multiPin1=num%2;
    num=num/2;
    multiPin2=num%2;
    num=num/2;
    multiPin3=num%2;
    wait(0.05);
    return readLight.read();
}

void fillWater(float maxHeight)
{
    int fillorNot=0;
    int interrupeorNot=0;
    printf("Fill water mission running ...\n\r");
    while((fillorNot<tolerateError+1)&&(interrupeorNot<tolerateError+1)) {
        float waterlevelNow=getDepth_waterlevel();
        if(waterlevelNow > maxHeight) {//可能已經到達指定高
            fillorNot++;
        } else {
            fillorNot=0;
            faucet=1;
        }
        if(waterlevelNow < groundHeight) { //可能杯子被拿走了
            interrupeorNot++;
        } else {
            interrupeorNot=0;
            faucet=1;
            /*
            //if(loading<(waterlevelNow/maxHeight)*100) {
            if((waterlevelNow/maxHeight)*100>0){
                loading=(waterlevelNow/maxHeight)*100;
                printf("Fill water mission loading ... %.2f%%\n\r",loading);
            */
            printf("current water level:%.3f      target level:%.3f\n\r",waterlevelNow,maxHeight);
        }
    }
    faucet=0;
    printf("Water filled, mission complete!!\n\r");
}

void putDataToStorage()
{
    for(int i=0; i<=14; i++)lightValue[i]=readLightFromMulti(i);
    for(int i=0; i<14; ++i)diffBTWlightValue[i]=lightValue[i+1]-lightValue[i];
}

void containerFound2()
{
    bool flag=false;
    while(true) {
        putDataToStorage();
        //test the read light function
        //for(int i=0; i<=14; i++) printf("lightValue index %d : %f\n\r",i,lightValue[i]);
        //for(int i=0; i<14; i++) printf("diffBTWlightValue index %d : %f\n\r",i,diffBTWlightValue[i]);
        for(int i=0; i<14; ++i) {
            if(diffBTWlightValue[i]>triggerLightStrength) {
                maxHeight=lightValueHeight[14-i];
                printf("container height checked!\n\r");
                flag=true;
                break;
            }
        }
        if(flag==true) break;
    }
}

void containerFound()
{
    bool flag=false;
    while(true) {
        putDataToStorage();
        //test the read light function
        //for(int i=0; i<=14; i++) printf("lightValue index %d : %f\n\r",i,lightValue[i]);
        //for(int i=0; i<14; i++) printf("diffBTWlightValue index %d : %f\n\r",i,diffBTWlightValue[i]);
        for(int i=0; i<14; ++i) {
            if(diffBTWlightValue[i]>triggerLightStrength) {
                printf("\n\rStep 2.--------------------\n\r");
                printf("Container found!!\n\r");
                printf("wait 1 sec for check container height...\n\r");
                wait(1);
                containerFound2();
                flag=true;
                break;
            }
        }
        if(flag==true) break;
    }
}

void getContainerBot()
{
    for(int i=0; i<10; i++) {
        getDepth_waterlevel();
    }
}

void waitingRemove()
{
    int removeorNot=0;
    while(removeorNot<tolerateError+1) { //wait for user remove cup
        if(getDepth_waterlevel()<=groundHeight) removeorNot++;
    }
}

int main()
{
    LED=1;
    wait(5);
    while(true) {
        printf("\n\rStep 1.--------------------\n\r");
        printf("Ready to fill water!\n\r");
        printf("Sensing container...\n\r");

        //printf("\n\rStep 2.--------------------\n\r");
        containerFound();
        //printf("trigger photoresistance gap number(from up to down) = %i\n\r",i);
        //printf("trigger diff value = %f\n\rtarget height(cm) = %.3f\n\r",diffBTWlightValue[i]);
        //printf("ground height(cm) = %.3f\n\r",maxHeight);
        printf("Wait 1 sec for start mission.\n\r");
        wait(1);

        printf("\n\rStep 3.--------------------\n\r");
        fillWater(maxHeight);

        printf("\n\rStep 4.--------------------\n\r");
        printf("Please remove your cup to start next mission...\n\r");
        waitingRemove();
        printf("Thank you :)\n\r");
        printf("Wait 1.5 sec for start next mission.\n\r");
        printf("*********************************************************\n\r");
        wait(1.5);
    }
}

