#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>
#include <arpa/inet.h>
#include "newheader.h"

 int main(int argc,char *argv[])
 {
   int sockfd,newsockfd,portno,n;
   socklen_t clilen;
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
   FILE *fp;
   char buff[50];
   int command;
   read(newsockfd,buff,50);
   command=buff[0];
   
   if(command==1)
   {
   int j,i,k,p;
   long int pos;
   char str[1];
   printf("add the data\n");
   fp=fopen("base.txt","a");
	i=buff[2];
	k=buff[3];
	j=buff[k+4];
	p=buff[k+5];
	pos=ftell(fp);
	fseek(fp,pos,SEEK_SET);
	str[0]=buff[1];
	fwrite(str,sizeof(str),1,fp);
    	switch(i)
	{
		case 1:	
			fseek(fp,pos+2,SEEK_SET);
			strcpy(dname,&buff[4]);
        		memset(&dname[k],0,sizeof(dname)); 
			fwrite(dname,sizeof(dname),1,fp);
			printf("\n\ndname is%s",dname);
		break;
		case 2:
			fseek(fp,pos+2,SEEK_SET);
			strcpy(dname,&buff[k+6]);
        		memset(&dname[p],0,sizeof(dname)); 
			fwrite(dname,sizeof(dname),1,fp);
			printf("\n\ndname is%s",dname);
		break;
	}
	switch(j)
	{

	case 1:
   		fseek(fp,pos+21,SEEK_SET);
		strcpy(dlocation,&buff[4]);
        	memset(&dlocation[k],0,sizeof(dlocation)); 
		fwrite(dlocation,sizeof(dlocation),1,fp);
		printf("\n\ndlocation is%s",dlocation);
	break;
	case 2:
		fseek(fp,pos+21,SEEK_SET);
		strcpy(dlocation,&buff[k+6]); 
		printf("\n\ndlocation is%s",dlocation);
		fwrite(dlocation,sizeof(dlocation),1,fp);
	break;
	}
   fclose(fp);
   }
   else if(command==2)
   {
     printf("displaying the data\n");
     char dn[MAX],dl[MAX],ch,data[50];
     int pos=0,l,p;
     fp=fopen("base.txt","r");
    	d=buff[1];
	while(ch!=EOF)
	{
        fseek(fp,pos,SEEK_SET);
	ch = fgetc(fp);
		if(ch==d)
       		{
		data[0]=d;
			
   		fseek(fp,pos+1,SEEK_SET);
		fread(dn,sizeof(dn),1,fp);
		l=strlen(dn);
		data[1]=l;
		memcpy(&data[2],dn,l);
			
		fseek(fp,pos+21,SEEK_SET);
		fread(dl,sizeof(dl),1,fp);
		p=strlen(dl);
		data[l+2]=p;
		memcpy(&data[l+3],dl,p);
			
     		write(newsockfd,data,strlen(data));
		break;
		}
	pos=pos+OFFSET;
	}
  }

  else if(command==3)
  {
  printf("edit the data\n");
  int pos=0,k,attid; 
  char s,ch1;
  s=buff[1];
  attid=buff[2];
  fp=fopen("base.txt","r+");
  k=buff[3];
 
  while(ch1!=EOF)
   {
        fseek(fp,pos,SEEK_SET);
	ch1 = fgetc(fp);
	if(ch1==s)
	{
	if(attid==1)
	{
	strcpy(dname,&buff[4]); 
	fseek(fp,pos+1,SEEK_SET);
	fwrite(dname,sizeof(dname),1,fp);
	}
	else if(attid==2)
	{
	strcpy(dlocation,&buff[4]); 
	fseek(fp,pos+21,SEEK_SET);
	fwrite(dlocation,sizeof(dlocation),1,fp);
	}
	else if(attid==3)
	{
	fseek(fp,pos+1,SEEK_SET);
	strcpy(dname,&buff[4]);
	memset(&dname[k],0,sizeof(dname));
	fwrite(dname,sizeof(dname),1,fp);

	strcpy(dlocation,&buff[k+5]);
	fseek(fp,pos+21,SEEK_SET);
	fwrite(dlocation,sizeof(dlocation),1,fp);
	}
	break;
	}
  pos=pos+OFFSET;
  }
  fclose(fp);
  }
  else if(command==4)
  {  
  printf("remmove the data\n");
  int pos=0,i;
  long int numbytes;
  char k,ch1;
  char *mtr,*ptr;
  k=buff[1];
  fp=fopen("base.txt","r");
  fseek(fp,0,SEEK_END);
  numbytes = ftell(fp);
  fseek(fp,0,SEEK_SET);
  mtr = (char*)calloc(numbytes, sizeof(char));
  printf("ftell %ld\n",numbytes);
  fread(mtr,sizeof(char),numbytes,fp);
 	while(ch1!=EOF)
	{
	fseek(fp,pos,SEEK_SET);
	ch1 = fgetc(fp);
	printf("id is %d",ch1);
		if(ch1==k)
		{
		printf("position %d",pos);
		for(i=pos;i<numbytes;i++)
		{
		mtr[i]=mtr[i+41];
		}
		break;		
		}
	pos=pos+OFFSET;
	}
   fclose(fp);
   int r=numbytes-41;
   fp=fopen("base.txt","w");
   fwrite(mtr,1,r,fp);
   fclose(fp);
   free(mtr);
  }
}   	
}	
}
close(newsockfd);
return 0;
}
