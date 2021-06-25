#include "controlDevices.h"




int fireInit(int pinNum)
{
    pinMode(pinNum,INPUT);
    digitalWrite(pinNum,HIGH);
    pinMode(29,OUTPUT);
    digitalWrite(29,HIGH);//蜂鸣器初始化

}

int fireStatusRead(int pinNum)
{
    return digitalRead(pinNum);
}


struct Devices fire=
{
    .deviceName="fireIfOrNot",
    .pinNum=25,
    .deviceInit=fireInit,
    .readStatus=fireStatusRead

};

struct Devices* addFireToDeviceLink(struct Devices* phead)

{

    if (phead==NULL){
        return &fire;

    }
    else{

    fire.next=phead;
    phead=&fire;
    }


}
