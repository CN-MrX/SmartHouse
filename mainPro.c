#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <pthread.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "controlDevices.h"
#include "inputCmd.h"
//-----------------------------------全局变量--------------------------------------------
struct Devices *pdeviceHead=NULL;
struct inputCommander *pcommandHead=NULL;
struct inputCommander* socketHandler;
int c_fd;

//-------------------------------------------------------------------------------------


struct Devices* findDeviceByName(char*  name,struct Devices *phead)
{
    struct Devices*tmp=phead;

    if(phead==NULL){
        return NULL;
    }else{
        while(tmp!=NULL)
        {
            if(strcmp(tmp->deviceName,name)==0){
                return tmp;
                }
            tmp=tmp->next;
        }

        return NULL;
    }
}

struct Devices* initDevice(struct Devices *phead)
{
    struct Devices*tmp=phead;

    if(phead==NULL){
        return NULL;
    }else{
        while(tmp!=NULL)
        {
            tmp->deviceInit(tmp->pinNum);
            tmp=tmp->next;
        }

        return NULL;
    }
}


struct inputCommander* findCommandByName(char*  name,struct inputCommander *phead)
{
    struct inputCommander*tmp=phead;

    if(phead==NULL){
        return NULL;
    }else{
        while(tmp!=NULL)
        {
            if(strcmp(tmp->commandName,name)==0){
                return tmp;
                }
            tmp=tmp->next;
        }

        return NULL;
    }
}

void * voice_thread(void *data)
{
    struct inputCommander* voiceHandler;
    int nread;
    char name[128]={'\0'};

    

        
    voiceHandler=findCommandByName("voice",pcommandHead);

    if(voiceHandler==NULL)
    {
        printf("find voicehandler error\n");   
        pthread_exit(NULL);
    }
    else
    {
        if(voiceHandler->Init(voiceHandler,NULL,NULL)<0)
        {

            printf("voicehandler init error\n");
            pthread_exit(NULL);
        }else
        {
            printf("%s init success\n",voiceHandler->commandName);
        }
        

        initDevice(pdeviceHead);//初始化



        while(1){


            memset(name,'\0',128);
        
            nread=voiceHandler->getCommand(voiceHandler);
            if(nread>0)
            {
              
                printf("command=%s",voiceHandler->command);

                if(strstr(voiceHandler->command,"open 1")!=0)
                {
                    strcpy(name,"bathroomLight");
                    struct Devices*tmp=NULL;
                    tmp=(struct Devices*)malloc(sizeof(struct Devices));
                    tmp=findDeviceByName(name,pdeviceHead);
                    tmp->open(tmp->pinNum);
                    printf("open 1 success\n");
                    
   
                }else if(strstr(voiceHandler->command,"close 1")!=0)
                {
                    strcpy(name,"bathroomLight");
                    struct Devices*tmp=NULL;
                    tmp=(struct Devices*)malloc(sizeof(struct Devices));
                    tmp=findDeviceByName(name,pdeviceHead);
                    tmp->close(tmp->pinNum);
                    printf("close 1 success\n");

                }else if(strstr(voiceHandler->command,"open 2")!=0)
                {
                    strcpy(name,"upstairLight");
                    struct Devices*tmp=NULL;
                    tmp=(struct Devices*)malloc(sizeof(struct Devices));
                    tmp=findDeviceByName(name,pdeviceHead);
                    tmp->open(tmp->pinNum);
                    printf("open 2 success\n");

                }else if(strstr(voiceHandler->command,"close 2")!=0)
                {
                    strcpy(name,"upstairLight");

                    struct Devices*tmp=NULL;
                    tmp=(struct Devices*)malloc(sizeof(struct Devices));
                    tmp=findDeviceByName(name,pdeviceHead);
                    tmp->close(tmp->pinNum);
                    printf("close 2 success\n");

                }else if(strstr(voiceHandler->command,"open 3")!=0)
                {
                    strcpy(name,"livingRoomLight");

                    struct Devices*tmp=NULL;
                    tmp=(struct Devices*)malloc(sizeof(struct Devices));
                    tmp=findDeviceByName(name,pdeviceHead);
                    tmp->open(tmp->pinNum);
                    printf("open 3 success\n");

                }else if(strstr(voiceHandler->command,"close 3")!=0)
                {
                    strcpy(name,"livingRoomLight");

                    struct Devices*tmp=NULL;
                    tmp=(struct Devices*)malloc(sizeof(struct Devices));
                    tmp=findDeviceByName(name,pdeviceHead);
                    tmp->close(tmp->pinNum);
                    printf("close 3 success\n");

                }else if(strstr(voiceHandler->command,"open 4")!=0)
                {
                    strcpy(name,"diningroomLight");

                    struct Devices*tmp=NULL;
                    tmp=(struct Devices*)malloc(sizeof(struct Devices));
                    tmp=findDeviceByName(name,pdeviceHead);
                    tmp->open(tmp->pinNum);
                    printf("open 4 success\n");

                }else if(strstr(voiceHandler->command,"close 4")!=0)
                {
                    strcpy(name,"diningroomLight");

                    struct Devices*tmp=NULL;
                    tmp=(struct Devices*)malloc(sizeof(struct Devices));
                    tmp=findDeviceByName(name,pdeviceHead);
                    tmp->close(tmp->pinNum);
                    printf("close 4 success\n");

                }
    
            }
        }

    }


}
void* read_thread(void *data)
{
    memset(socketHandler->command,'\0',sizeof(socketHandler->command));
    int n_read=read(c_fd,socketHandler->command,sizeof(socketHandler->command));
    char name[128]={'\0'};

    if(n_read==-1)
    {
        perror("read");
    }else
    {
        printf("read from clinet: %s\n",socketHandler->command);

                  if(strstr(socketHandler->command,"open 1")!=0)
                {
                    strcpy(name,"bathroomLight");
                    struct Devices*tmp=NULL;
                    tmp=(struct Devices*)malloc(sizeof(struct Devices));
                    tmp=findDeviceByName(name,pdeviceHead);
                    tmp->open(tmp->pinNum);
                    printf("open 1 success\n");
                    
   
                }else if(strstr(socketHandler->command,"close 1")!=0)
                {
                    strcpy(name,"bathroomLight");
                    struct Devices*tmp=NULL;
                    tmp=(struct Devices*)malloc(sizeof(struct Devices));
                    tmp=findDeviceByName(name,pdeviceHead);
                    tmp->close(tmp->pinNum);
                    printf("close 1 success\n");

                }else if(strstr(socketHandler->command,"open 2")!=0)
                {
                    strcpy(name,"upstairLight");
                    struct Devices*tmp=NULL;
                    tmp=(struct Devices*)malloc(sizeof(struct Devices));
                    tmp=findDeviceByName(name,pdeviceHead);
                    tmp->open(tmp->pinNum);
                    printf("open 2 success\n");

                }else if(strstr(socketHandler->command,"close 2")!=0)
                {
                    strcpy(name,"upstairLight");

                    struct Devices*tmp=NULL;
                    tmp=(struct Devices*)malloc(sizeof(struct Devices));
                    tmp=findDeviceByName(name,pdeviceHead);
                    tmp->close(tmp->pinNum);
                    printf("close 2 success\n");

                }else if(strstr(socketHandler->command,"open 3")!=0)
                {
                    strcpy(name,"livingRoomLight");

                    struct Devices*tmp=NULL;
                    tmp=(struct Devices*)malloc(sizeof(struct Devices));
                    tmp=findDeviceByName(name,pdeviceHead);
                    tmp->open(tmp->pinNum);
                    printf("open 3 success\n");

                }else if(strstr(socketHandler->command,"close 3")!=0)
                {
                    strcpy(name,"livingRoomLight");

                    struct Devices*tmp=NULL;
                    tmp=(struct Devices*)malloc(sizeof(struct Devices));
                    tmp=findDeviceByName(name,pdeviceHead);
                    tmp->close(tmp->pinNum);
                    printf("close 3 success\n");

                }else if(strstr(socketHandler->command,"open 4")!=0)
                {
                    strcpy(name,"diningroomLight");

                    struct Devices*tmp=NULL;
                    tmp=(struct Devices*)malloc(sizeof(struct Devices));
                    tmp=findDeviceByName(name,pdeviceHead);
                    tmp->open(tmp->pinNum);
                    printf("open 4 success\n");

                }else if(strstr(socketHandler->command,"close 4")!=0)
                {
                    strcpy(name,"diningroomLight");

                    struct Devices*tmp=NULL;
                    tmp=(struct Devices*)malloc(sizeof(struct Devices));
                    tmp=findDeviceByName(name,pdeviceHead);
                    tmp->close(tmp->pinNum);
                    printf("close 4 success\n");

                }
    }


}



void* socket_thread(void *data)
{

    struct sockaddr_in c_addr;
    memset(&c_addr,0,sizeof(c_addr));
    int sof=sizeof(struct sockaddr_in);

    int nread;
    pthread_t readThread;
    
    
    socketHandler=findCommandByName("socketServer",pcommandHead);

    if(socketHandler==NULL)
    {
        printf("find sockethandler error\n");   
        pthread_exit(NULL);
    }else
        {
            printf("%s init success\n",socketHandler->commandName);
        }
    socketHandler->Init(socketHandler,NULL,NULL);
    while(1)
    {
        c_fd=accept(socketHandler->sfd,(struct sockaddr *)&c_addr,&sof);
        pthread_create(&readThread,NULL,read_thread,NULL);




    }



}


void *fire_thread(void *data)
{
    struct Devices* fireHandler=NULL;


    

        
    fireHandler=findDeviceByName("fireIfOrNot",pdeviceHead);

    fireHandler->deviceInit(fireHandler->pinNum);
    printf("fire init success\n");

    while(1)
    {
        if(fireHandler->readStatus(fireHandler->pinNum)==0)
        {
            digitalWrite(29,LOW);
            
        }else
        {
            digitalWrite(29,HIGH);
        }


    }



}

int main()
{
    pthread_t voiceThread;
    pthread_t socketThread;
    pthread_t fireThread;



//---------------------------设备控制工厂初始化-----------------------------


    pdeviceHead= addBathroomToDeviceLink(pdeviceHead);
    pdeviceHead= addUpstairToDeviceLink(pdeviceHead);
    pdeviceHead= addLivingRoomToDeviceLink(pdeviceHead);
    pdeviceHead= addDiningroomToDeviceLink(pdeviceHead);
    pdeviceHead= addFireToDeviceLink(pdeviceHead);
//-------------------------------------------------------------------------


printf("devices init\n");
//--------------------------指令控制工厂初始化------------------------------


    pcommandHead=addvoiceControlToInputCommandLink(pcommandHead);
    pcommandHead=addsocketControlToInputCommandLink(pcommandHead);
//-------------------------------------------------------------------------   
    
    printf("command init\n");

    if(wiringPiSetup()==-1)
    {
        return -1;
    }



//线程建立

//线程1：语音
pthread_create(&voiceThread,NULL,voice_thread,NULL);
//线程2：socket
pthread_create(&socketThread,NULL,socket_thread,NULL);

//线程3：摄像头

//线程4：火灾
pthread_create(&fireThread,NULL,fire_thread,NULL);

pthread_join(voiceThread,NULL);
pthread_join(socketThread,NULL);
pthread_join(fireThread,NULL);


//------------------------------测试代码----------------------------------
   /* char* name="diningroomLight";
    if(wiringPiSetup()==-1)
    {
        return -1;
    }


    struct Devices*tmp=findDeviceByName(name,pdeviceHead);

    if(tmp!=NULL)
    {
        
        int msg;
        tmp->deviceInit(tmp->pinNum);
        while(1){
            printf("light on/off:");
            scanf("%d",&msg);
            if(msg==1)
            {
        tmp->open(tmp->pinNum);
            }else{
                tmp->close(tmp->pinNum);

            }
        }
    }
*/
//------------------------------------------------------------------------






    return 0;
}
