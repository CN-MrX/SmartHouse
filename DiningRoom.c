#include "controlDevices.h"


int diningroomOpen(int pinNum)
{
digitalWrite(pinNum,LOW);

}

int diningroomClose(int pinNum)
{

digitalWrite(pinNum,HIGH);


}

int diningroomInit(int pinNum)
{
    pinMode(pinNum,OUTPUT);
    digitalWrite(pinNum,HIGH);

}

int diningroomCloseStatus(int status)
{

}


struct Devices diningroom=
{
    .deviceName="diningroomLight",
    .pinNum=24,
    .open=diningroomOpen,
    .close=diningroomClose,
    .deviceInit=diningroomInit,
    .changeStatus=diningroomCloseStatus

};

struct Devices* addDiningroomToDeviceLink(struct Devices* phead)

{

    if (phead==NULL){
        return &diningroom;

    }
    else{

    diningroom.next=phead;
    phead=&diningroom;
    }


}

