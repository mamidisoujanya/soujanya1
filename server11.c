
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>
#include<arpa/inet.h>
#include "newheader.h"

 int main(int argc,char *argv[])
 {
   int sockfd,newsockfd,portno,n;
   socklen_t clilen;
   char buff[50];
   pid_t childpid;
   struct sockaddr_in servaddr,cliaddr;
   if(argc<2)
   {
   fprintf(stderr,"error no port provided\n");
   exit(1);
   }

   sockfd=socket(AF_INET,SOCK_STREAM,0);
   if(sockfd<0)
   perror("error opening file");

   memset(&servaddr,'\0',sizeof(servaddr));
   portno=atoi(argv[1]);
   servaddr.sin_family=AF_INET;
   servaddr.sin_addr.s_addr=INADDR_ANY;
   servaddr.sin_port=htons(portno);
   if(bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0)
   perror("error in binding");

   listen(sockfd,5);

   while(1)
   {
   clilen=sizeof(cliaddr);
   newsockfd=accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);
   if(newsockfd<0){
    perror("error on accept");
   }
   printf("Connection accepted from %s:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
   if((childpid=fork())==0)
   {
   close(sockfd);
   while(1)
   {
   FILE *fp ,*fp1;
   int command;
   read(newsockfd,buff,50);
   command=buff[0];
   attid=buff[2];

   if(command==1)
   {
   int j,i;
   //static int i;
   long int pos;
   char str[2];
   printf("add the data\n");
   fp=fopen("base.txt","a");
	i=buff[2];
	j=buff[25];
	str[1]=buff[1];
	strcpy(dname,&buff[4]); 
	strcpy(dlocation,&buff[27]); 
 
	pos=ftell(fp);
	printf("posis %ld",pos);
	fseek(fp,pos,SEEK_SET);
	fwrite(str,sizeof(str),1,fp);
    	if(1==i)
	{
	fseek(fp,pos+2,SEEK_SET);
	fwrite(dname,sizeof(dname),1,fp);
	}
	if(2==j)
	{
	fseek(fp,pos+22,SEEK_SET);
	fwrite(dlocation,sizeof(dlocation),1,fp);
	}
   //i++;
   fclose(fp);
   }
	
  else if(command==2)
  {
   printf("displaying the data\n");
    char data[50];
    int pos,k,did1;
    char dn[ATTLEN],dl[ATTLEN];
    
    	k=buff[1];
	fp=fopen("base.txt","r");
	pos=(k-1)*OFFSET;
	printf("posis %d",pos);
	fseek(fp,pos+1,SEEK_SET);
	fread(&did1,sizeof(did1),1,fp);
	data[1]=did1;
   
	fseek(fp,pos+2,SEEK_SET);
	fread(dn,sizeof(dn),1,fp);
	strcpy(&data[4],dn);

	fseek(fp,pos+22,SEEK_SET);
	fread(dl,sizeof(dl),1,fp);
	strcpy(&data[27],dl);

   write(newsockfd,data,sizeof(data)); 
  }

  else if(command==3)
  {
  printf("edit the data\n");
  fp=fopen("base.txt","r+");
  int s,pos; 
  s=buff[1];
  strcpy(dname,&buff[4]); 
  strcpy(dlocation,&buff[27]); 
  printf("enter id is %d:",s);  
  printf("att %d:",attid);
  pos=(s-1)*OFFSET;

	if(attid==1)
	{
	fseek(fp,pos+2,SEEK_SET);
	fwrite(dname,sizeof(dname),1,fp);
	}
	else if(attid==2)
	{
	fseek(fp,pos+22,SEEK_SET);
	fwrite(dlocation,sizeof(dlocation),1,fp);
	}
	else if(attid==3)
	{
	fseek(fp,pos+2,SEEK_SET);
	fwrite(dname,sizeof(dname),1,fp);

	fseek(fp,pos+22,SEEK_SET);
	fwrite(dlocation,sizeof(dlocation),1,fp);
	}
	
  fclose(fp);
  }
  else if(command==4)
  {  
  printf("remmove the data\n");
  int k,pos;
  char c[2];
  fp=fopen("base.txt","r+");
 
	k=buff[1];
	pos=(k-1)*OFFSET;
	fseek(fp,pos+1,SEEK_SET);
	fwrite(c,sizeof(c),1,fp);
	fseek(fp,pos+2,SEEK_SET);
	fwrite(dname,sizeof(dname),1,fp);
	fseek(fp,pos+22,SEEK_SET);
	fwrite(dlocation,sizeof(dlocation),1,fp);
    
 fclose(fp);
 }
 }   	
 }	
 }
close(newsockfd);
 return 0;
 }







