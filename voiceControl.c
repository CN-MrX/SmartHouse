#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "inputCmd.h"

int voiceGetCommand(struct inputCommander *voicer)
{
    int nread=0;
    memset(&voicer->command,0,sizeof(voicer->command));//new
    nread=read(voicer->fd,voicer->command,sizeof(voicer->command));
    if(nread==0)
    {
        //printf("out of time\n");
    }else
    {
        return nread;

    }

}

int voiceInit(struct inputCommander *voicer,char *ipAdress,char *port)
{
    int fd=0;
    fd=serialOpen(voicer->deviceName,9600);
    if(fd==-1)
    {
        printf("serialOpen error");
        exit(-1);
    }
    voicer->fd=fd;
    return fd;

}
struct inputCommander voiceControl=
{   .commandName="voice",
    .deviceName="/dev/ttyAMA0",
    .command={'\0'},
    .Init=voiceInit,
    .getCommand=voiceGetCommand,
    .log={'\0'},
    .next=NULL
};


struct inputCommander* addvoiceControlToInputCommandLink(struct inputCommander* phead)

{

    if (phead==NULL){
        return &voiceControl;

    }
    else{

    voiceControl.next=phead;
    phead=&voiceControl;
    }


}

