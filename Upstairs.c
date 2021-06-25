#include "controlDevices.h"


int upstairOpen(int pinNum)
{
digitalWrite(pinNum,LOW);

}

int upstairClose(int pinNum)
{

digitalWrite(pinNum,HIGH);


}

int upstairInit(int pinNum)
{
    pinMode(pinNum,OUTPUT);
    digitalWrite(pinNum,HIGH);

}

int upstairCloseStatus(int status)
{

}


struct Devices upstair=
{
    .deviceName="upstairLight",
    .pinNum=21,
    .open=upstairOpen,
    .close=upstairClose,
    .deviceInit=upstairInit,
    .changeStatus=upstairCloseStatus

};

struct Devices* addUpstairToDeviceLink(struct Devices* phead)

{

    if (phead==NULL){
        return &upstair;

    }
    else{

    upstair.next=phead;
    phead=&upstair;
    }


}

