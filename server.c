
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

 // while(1)
 //  {
   clilen=sizeof(cliaddr);
   newsockfd=accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);
   if(newsockfd<0){
    perror("error on accept");
   }
   //printf("Connection accepted from %s:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
   //if((childpid=fork())==0)
  // {
   //close(sockfd);
   //while(1)
  // {
   FILE *fp ,*fp1;
   int command;
   read(newsockfd,buff,50);
   command=buff[0];
   attid=buff[2];

   if(command==1)
   {
   int j,i,k,m,m2;
   long int pos;
   char str[1];
   printf("add the data\n");
   fp=fopen("base.txt","a");
	i=buff[2];
	printf("i is %d",i);
	k=buff[3];
printf("k is %d",k);
	m=k+5;
	m2=m+2;
printf("m2 is %d",m2);
	j=buff[m];
printf("j is %d",j);
	
	
	
	pos=ftell(fp);
	printf("posis %ld",pos);
	fseek(fp,pos,SEEK_SET);
	 str[0]=buff[1];
	fwrite(str,sizeof(str),1,fp);
    	//if(1==i)
	//{
	fseek(fp,pos+1,SEEK_SET);
	strcpy(dname,&buff[4]);
	fwrite(dname,sizeof(dname),1,fp);
	//}
	//if(2==j)
	//{
	fseek(fp,pos+22,SEEK_SET);
	strcpy(dlocation,&buff[27]); 
	fwrite(dlocation,sizeof(dlocation),1,fp);
	//}
   
   fclose(fp);
   }
	
  else if(command==2)
  {
     printf("displaying the data\n");
     char data[50];
     int pos=0,did1,id;
     char dn[MAX],dl[MAX],ch,k;
     
    	k=buff[1];
	fp=fopen("base.txt","r");
	//pos=(k-1)*OFFSET;
	while(ch!=EOF)
	{
        fseek(fp,pos,SEEK_SET);
	ch = fgetc(fp);
	//id = atoi(&ch);

		if(ch==k)
       		{
		printf("id is %d",ch);
		fseek(fp,pos,SEEK_SET);
		fread(&did1,sizeof(did1),1,fp);
		data[1]=did1;
   
		fseek(fp,pos+1,SEEK_SET);
		fread(dn,sizeof(dn),1,fp);
		strcpy(&data[4],dn);

		fseek(fp,pos+21,SEEK_SET);
		fread(dl,sizeof(dl),1,fp);
		strcpy(&data[27],dl);

     		write(newsockfd,data,sizeof(data));
		break;
		}
		//else
		//{
		pos=pos+OFFSET;
		//printf("posis %d",pos);
		//}
	}
  }

  else if(command==3)
  {
  printf("edit the data\n");
  
  int pos=0; 
  char s,ch1;
  s=buff[1];
fp=fopen("base.txt","r+");
  strcpy(dname,&buff[4]); 
  strcpy(dlocation,&buff[27]); 
  //printf("enter id is %d:",s);  
  printf("att %d:",attid);
 // pos=(s-1)*OFFSET;
while(ch1!=EOF)
{
        fseek(fp,pos,SEEK_SET);
	ch1 = fgetc(fp);
	printf("id is %d",ch1);
	if(ch1==s)
	{
	if(attid==1)
	{
	fseek(fp,pos+1,SEEK_SET);
	fwrite(dname,sizeof(dname),1,fp);
	}
	else if(attid==2)
	{
	fseek(fp,pos+21,SEEK_SET);
	fwrite(dlocation,sizeof(dlocation),1,fp);
	}
	else if(attid==3)
	{
	fseek(fp,pos+1,SEEK_SET);
	fwrite(dname,sizeof(dname),1,fp);

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
  int pos=0;
  char data[41],k,ch1;
  //char *mtr,*ptr;
  //mtr=(char*)malloc(500*sizeof(char));
  //memset(mtr,0,500*sizeof(char));
  //ptr=mtr;
  k=buff[1];
  fp=fopen("base.txt","r");
  fp1=fopen("xxx.txt","a");
	while(ch1!=EOF &&(fgets(data,41,fp)!=NULL))
	{
        fseek(fp,pos,SEEK_SET);
	ch1 = fgetc(fp);
	//fgets(data,41,fp);
	printf("id is %d",ch1);
	
		if(ch1!=k)
		{
  		//printf("data is %s",data);
		//strcpy(ptr,data);
		//ptr=ptr+strlen(data);
		
		fputs(data,fp1);
		}
	pos=pos+OFFSET;
	}
fclose(fp);
fclose(fp1);
remove("base.txt");
rename("xxx.txt","base.txt");
 //fp=fopen("base.txt","w");
//fputs(ptr,fp);
  }
 
//}   	
//}	
//}
//close(newsockfd);
return 0;
}







