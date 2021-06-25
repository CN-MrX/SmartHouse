#include <wiringPi.h>
#include <stdio.h>
struct Devices
{
    char deviceName[128];
    int status;
    int pinNum;

    int (*open)(int pinNum);
    int (*close)(int pinNum);
    int (*deviceInit)(int pinNum);

    int (*readStatus)();
    int (*changeStatus)(int status);

    struct Devices *next;



};


struct Devices* addBathroomToDeviceLink(struct Devices* phead);
struct Devices* addUpstairToDeviceLink(struct Devices* phead);
struct Devices* addLivingRoomToDeviceLink(struct Devices* phead);
struct Devices* addDiningroomToDeviceLink(struct Devices* phead);
struct Devices* addFireToDeviceLink(struct Devices* phead);



