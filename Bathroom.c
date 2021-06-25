#include "controlDevices.h"


int bathroomOpen(int pinNum)
{
digitalWrite(pinNum,LOW);

}

int bathroomClose(int pinNum)
{

digitalWrite(pinNum,HIGH);


}

int bathroomInit(int pinNum)
{
    pinMode(pinNum,OUTPUT);
    digitalWrite(pinNum,HIGH);

}

int bathroomCloseStatus(int status)
{

}


struct Devices bathroom=
{
    .deviceName="bathroomLight",
    .pinNum=22,
    .open=bathroomOpen,
    .close=bathroomClose,
    .deviceInit=bathroomInit,
    .changeStatus=bathroomCloseStatus

};

struct Devices* addBathroomToDeviceLink(struct Devices* phead)

{

    if (phead==NULL){
        return &bathroom;

    }
    else{

    bathroom.next=phead;
    phead=&bathroom;
    }


}