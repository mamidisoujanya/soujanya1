#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "depot.h"
//#include "assert.h"
struct devicedata {
    int id;
    char name[20];
    char location[20];
    char manufacturer[20];
    int lastmodifiedtime;
};
struct dvPair {
     int id; 
    char value[20];
};

int main()
{   
 	struct devicedata s;
	int id1;
	int m=0,*n;
	char *a=(char*)malloc(sizeof(s));;
	char *b="xyzwas";

	
	//printf("enter name\n");
	//scanf("%s",s.name);
	char *buffer=(char*)malloc(sizeof(s));
	memcpy(buffer,(const char*)&s,sizeof(s));
	
	DEPOT *temp = dpopen("thfile",DP_OWRITER | DP_OCREAT ,100);
	printf("%s\n",dperrmsg(dpecode));
	if(temp == NULL)
	{
	printf("temp is null");
	}
	else
	{
	printf("sucess");
	}
	//dpput(DEPOT *depot, const char *kbuf, int ksiz, const char *vbuf, int vsiz, int dmode);
	//dpput(temp,a,sizeof(a),buffer,sizeof(buffer),id1);
	//free(buffer);
	//char *dpget(DEPOT *depot, const char *kbuf, int ksiz, int start, int max, int *sp);
	char *fp=dpget(temp,a,sizeof(a),m,100,n);
	printf("data is %s",fp);
	//int dpout(DEPOT *depot, const char *kbuf, int ksiz);
	//dpout(temp,a,sizeof(a));
	dpclose(temp);
}







//fp=fopen("base.txt","a");
	//*kbuf=&id1;
  // printf("enter the id:\n");
  //  scanf("%d",id1);
    //printf("Enter name:\n ");
   // scanf("%s", sname);
	//strcpy(&b[0],sname);
    //printf("Enter location: \n");
   // scanf("%s", slocation);
	//s//trcpy(&b[1],slocation);
    //printf("Enter manufacturer name:\n");
    //scanf("%s", s.manufacturer);
    // printf("Enter lastModifiedTime:dsfsd \n");
    // scanf("%d",&s.lastmodifiedtime);
//dperrmsg(id1);













