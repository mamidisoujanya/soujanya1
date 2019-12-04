#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include<ctype.h>
#include<arpa/inet.h>
#include "newheader.h"

void error(const char *msg)
{
    perror(msg);
    exit(0);
}
int main(int argc, char *argv[])
{
int sockfd, portno, n;

struct sockaddr_in serv_addr;

struct hostent *server;

char buffer[50];

    if (argc < 3)
    {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);

       exit(0);
    }
portno = atoi(argv[2]);

sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) 

        perror("error opening socket");

server = gethostbyname(argv[1]);

     if (server == NULL) 
     {
        fprintf(stderr,"error, no such host\n");

        exit(0);
     }
memset(&serv_addr,'\0',sizeof(serv_addr));

serv_addr.sin_family = AF_INET;

bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);

serv_addr.sin_port = htons(portno);

if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 

   error("error connecting");
	
//while(1)
//{
int choice;

char packet[50];

printf("**---menu--**\n"); 

printf("enter the choice\n1.for add the device information\n2.for dispaly data\n3.edit the data\n4.remove the device\n5.exit\n");

scanf("%d",&choice);

packet[0]=choice;


if(choice==1)
{
	
	printf("add the info\n");

	printf("enter the device id:\n");

	scanf("%d",&did);

	packet[1]=did;
	
	printf("enter the attribute id 1 for add device name\n");	

	scanf("%d",&attid);
			
	if(attid==1)
	{

	packet[2]=attid;

	packet[3]=ATTLEN;//attribute length

	printf("enter device name length should be less than 20:\n");
	
	scanf("%19s",&packet[4]);

	}
	printf("enter the attribute id 2 for add device location\n");	
	
	scanf("%d",&attid);

	if(attid==2)
	{	
	packet[25]=attid;

	packet[26]=ATTLEN;//attribute length	

	printf("enter location length should be less than 20:\n");
	
	scanf("%19s",&packet[27]); 
	}
	write(sockfd,packet,sizeof(packet));

}
else if(choice==2)
{
        printf("enter the device id which one you want see:\n");

	scanf("%d",&did);

	packet[1]=did;

	write(sockfd,packet,2);
	
	n=read(sockfd,buffer,sizeof(buffer));

	  if (n < 0) 

	error("error in reading to socket");

	printf("device id :%d\n",buffer[1]);
	
	printf("device name :%s\n",&buffer[4]);
	
	printf("device location :%s\n",&buffer[27]);
}

else if(choice==3)
{
	
	printf("edit the data\n");
	
	printf("enter the device id which one you want change:\n");

	scanf("%d",&did);

	packet[1]=did;
		
	printf("enter attributeid\ni=1.for edit name \n2.for edit location \n3.edit all\n");

        scanf("%d",&attid);

	packet[2]=attid;
               
    	 if(attid==1)
	{
		packet[3]=ATTLEN;

      	        printf("enter device name length should be less than 20:\n");

	        scanf("%19s",&packet[4]);
	}    
 	else if(attid==2)
	{
		packet[26]=ATTLEN;		
		
		printf("enter location length should be less than 20:\n");

	        scanf("%19s",&packet[27]); 
	}
   	else if(attid==3)
	{	
 
	       packet[3]=ATTLEN;			
		
	       printf("enter device name length should be less than 20:\n");

	       scanf("%19s",&packet[4]);
		
	       packet[26]=ATTLEN;	

	       printf("enter location length should be less than 20:\n");

	       scanf("%19s",&packet[27]);

	}
write(sockfd,packet,sizeof(packet));

}

else if(choice==4)
{
	printf("remove the device\n");

	printf("enter the device id which one you want remove:\n");

	scanf("%d",&did);

	packet[1]=did;

	write(sockfd,packet,2);

}
else if(choice == 5)
{
printf("exit successfully");

close(sockfd);

exit(1);

}
//}

return 0;

}

