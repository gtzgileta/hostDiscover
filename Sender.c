#include <stdio.h>      
#include <sys/socket.h>
#include <arpa/inet.h>  
#include <stdlib.h>    
#include <string.h>    
#include <unistd.h>    
 
int main(int argc, char *argv[])
{
        int bcSock;                        
        struct sockaddr_in broadcastAddr;
        char *broadcastIP;                
        unsigned short broadcastPort;    
 
        char *sendString;                
 
        int broadcastPermission;          
        unsigned int sendStringLen;
 
        int status;
        int i;
 
    if (argc < 4)                    
    {
        fprintf(stderr,"Uso:  %s <Direcci�n IP> <Puerto> <Send String>\n", argv[0]);
        exit(1);
    }
 
    broadcastIP = argv[1];
    broadcastPort = atoi(argv[2]);
    sendString = argv[3];
 
        bcSock = socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
        if(bcSock == -1) {
                fprintf(stderr,"Can't create Socket");
                return 1;
        }
 
    broadcastPermission = 1;
    status = setsockopt(bcSock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission, sizeof(broadcastPermission);
    if(status == -1) {
                fprintf(stderr,"Can't set Broadcast Option");
                return 1;
    }
 
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));  
    broadcastAddr.sin_family = AF_INET;                
        inet_pton(AF_INET,broadcastIP,&broadcastAddr.sin_addr.s_addr);
    broadcastAddr.sin_port = htons(broadcastPort);        
 
    sendStringLen = strlen(sendString);  
        for(i=0; i<100; i++) {
                status = sendto(bcSock,sendString,sendStringLen,0,(struct sockaddr*)&broadcastAddr, sizeof(broadcastAddr));    
                printf("Send %i bytes to broadcast address\n",status);
        sleep(3);  
    }
}