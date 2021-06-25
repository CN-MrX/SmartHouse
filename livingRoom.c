#include "controlDevices.h"


int livingRoomOpen(int pinNum)
{
digitalWrite(pinNum,LOW);

}

int livingRoomClose(int pinNum)
{

digitalWrite(pinNum,HIGH);


}

int livingRoomInit(int pinNum)
{
    pinMode(pinNum,OUTPUT);
    digitalWrite(pinNum,HIGH);

}

int livingRoomCloseStatus(int status)
{

}


struct Devices livingRoom=
{
    .deviceName="livingRoomLight",
    .pinNum=23,
    .open=livingRoomOpen,
    .close=livingRoomClose,
    .deviceInit=livingRoomInit,
    .changeStatus=livingRoomCloseStatus

};

struct Devices* addLivingRoomToDeviceLink(struct Devices* phead)

{

    if (phead==NULL){
        return &livingRoom;

    }
    else{

    livingRoom.next=phead;
    phead=&livingRoom;
    }


}


