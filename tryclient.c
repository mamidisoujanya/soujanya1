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
	
while(1)
{
int choice;

char packet[50];

printf("**---menu--**\n"); 

printf("enter the choice\n1.for add the device information\n2.for dispaly data\n3.edit the data\n4.remove the device\n5.exit\n");

scanf("%d",&choice);

packet[0]=choice;

if(choice==1)
{
	int s,s1,l;

	enum Attid
		{
		name=1,
		location	
		};
	
	printf("add the info\n");

	printf("enter the device id:\n");

	scanf("%d",&did);

	packet[1]=did;
	
	printf("choose the option\n1.format1:name,location \n2.formate2:location,name\n");

	scanf("%d",&option);

	if(option==1)
	{
	packet[2]=name;

	printf("enter device name length should be less than 20:\n");
	
	scanf("%19s",dname);
	
	s=strlen(dname);	

	printf("s %d\n",s);
		
	packet[3]=s;
	
	strcpy(&packet[4],dname);

	printf("name is %s\n",&packet[4]);
	
	 while ((getchar()) != '\n'); 

	l=s+4;

	printf("l is %d\n",l);

	packet[l]=location;

	printf("enter device location length should be less than 20:\n");

	scanf("%19s",dlocation); 
	
	s1=strlen(dlocation);

	printf("s1 is %d\n",s1);

	packet[l+1]=s1;
	
	strcpy(&packet[l+2],dlocation);

	printf("location is %s\n",&packet[l+2]);

	}
	else if(option==2)
	{
	packet[2]=location;

	printf("enter device location length should be less than 20:\n");
	
	scanf("%19s",dlocation);
	
	s=strlen(dlocation);	

	printf("s %d\n",s);
		
	packet[3]=s;
	
	strcpy(&packet[4],dlocation);

	printf("location is %s\n",&packet[4]);
	
	 while ((getchar()) != '\n'); 

	l=s+4;

	printf("l is %d\n",l);

	packet[l]=name;

	printf("enter device name length should be less than 20:\n");

	scanf("%19s",dname); 
	
	s1=strlen(dname);

	printf("s1 is %d\n",s1);

	packet[l+1]=s1;
	
	strcpy(&packet[l+2],dname);

	printf("location is %s\n",&packet[l+2]);

	}
	temp=strlen(packet);
	
	printf("total packet is:\n");
	       
	for(i=0;i<temp;i++)
	{
	printf("packet is:%02x\t",packet[i]);
	}

	write(sockfd,packet,temp);
 }
else if(choice==2)
{
        int r,s;
	
	char buffer[50];

        printf("enter the device id which one you want see:\n");

	scanf("%d",&did);

	packet[1]=did;

	write(sockfd,packet,2);
	
	n=read(sockfd,buffer,sizeof(buffer));

	if (n < 0) 
	{
	error("error in reading to socket");
	}
	else
	{
	r=buffer[1];

	printf("device id :%d\n",buffer[0]);

	printf("device name :%.*s\n",r,&buffer[2]);

	s=buffer[r+2];
	
	printf("device location :%.*s\n",s,&buffer[r+3]);
	}
}

else if(choice==3)
{
	int s,s1,l1;
	
	printf("edit the data\n");
	
	printf("enter the device id which one you want change:\n");

	scanf("%d",&did);

	packet[1]=did;
		
	printf("enter attributeid\ni=1.for edit name \n2.for edit location \n3.edit all\n");

        scanf("%d",&attid);

	packet[2]=attid;
               
    	 if(attid==1)
	{
		printf("enter device name length should be less than 20:\n");
	
		scanf("%19s",dname);

		s=strlen(dname);
	
		printf("s %d\n",s);

		packet[3]=s;

		strcpy(&packet[4],dname);

	}    
 	else if(attid==2)
	{
		
		printf("enter device location length should be less than 20:\n");

		scanf("%19s",dlocation); 
	
		int s1=strlen(dlocation);
	
		packet[3]=s1;
	
		strcpy(&packet[4],dlocation);
	
	}
   	else if(attid==3)
	{	
 
	       printf("enter device name length should be less than 20:\n");
	
		scanf("%19s",dname);

		s=strlen(dname);
	
		printf("s %d\n",s);

		packet[3]=s;

		strcpy(&packet[4],dname);
		
		printf("enter device location length should be less than 20:\n");

		scanf("%19s",dlocation); 
	
		s1=strlen(dlocation);
	
		l1=s+4;

		packet[l1]=s1;
	
		strcpy(&packet[l1+1],dlocation);
	}
write(sockfd,packet,strlen(packet));
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
}
return 0;
}
