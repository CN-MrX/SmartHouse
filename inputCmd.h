struct inputCommander
{
    char commandName[128];
    char deviceName[128];
    char command[32];

    int (*Init)(struct inputCommander *voicer,char* ipAdress,char*port);
    int (*getCommand)(struct inputCommander *voicer);
    char log[1024];
    int fd;

    char port[12];
    char ipAdress[32];
    int sfd;
    
    struct inputCommander *next;


};


struct inputCommander* addvoiceControlToInputCommandLink(struct inputCommander* phead);
struct inputCommander* addsocketControlToInputCommandLink(struct inputCommander* phead);

