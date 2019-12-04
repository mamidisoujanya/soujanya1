
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "depot.h"
struct devicedata {
    int id;
    //int deviceType; //define some enumerations
    char name[20];
    char location[20];
    char manufacturer[20];
    int lastmodifiedtime;
}s;
struct dvPair {
    int type;
    int id; // to indicate the dvPair number
    char value[20];
}


void main()
{   
    //FILE *fp;
	int id1;
	//fp=fopen("base.txt","a");
	//*kbuf=&id1;
    //printf("enter the id:\n");
    //scanf("%d",id1);
   // printf("Enter name:\n ");
   // scanf("%s", s.name);
   // printf("Enter location: \n");
   // scanf("%s", s.location);
    //printf("Enter manufacturer name:\n");
    //scanf("%s", s.manufacturer);
     //printf("Enter lastModifiedTime: \n");
    // scanf("%d",&s.lastmodifiedtime);
dpopen("tempfile",DP_OCREAT,100);
//dpput(fp,&id1,sizeof(id1),0,0,id1);
}

