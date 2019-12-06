#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "depot.h"
struct devicedata {
   
    char name[20];
   char location[20];
  };
int main()
{
	int id1,i;
	int *n;
	char c;
	c='a';
	int m=0;
	const char *a="dcba";
	//const char *b="xyzw";
	//printf("c is %ld\n",sizeof(c));
	printf("a is %ld\n",sizeof(a));
	//const char spor[5] = {"diode"};
		
	DEPOT *temp = dpopen("jjfile",DP_OWRITER | DP_OCREAT,-1);
	printf("%s\n",dperrmsg(dpecode));
	printf("temp is executed\n");
	if(temp == NULL)
	{
	printf("temp is null\n");
	}
	else
	{
	printf("sucess\n");
	}
	struct devicedata s;
	printf("enter name\n");
	scanf("%s",s.name);
	printf("enter location\n");
	scanf("%s",s.location);
	
	 unsigned char *buffer=(char*)malloc(sizeof(s));
	printf("%ld\n",sizeof(buffer));
	
	
	//copying....
	memcpy(buffer,(char*)&s,sizeof(s));
	
	//printing..
	printf("Copied byte array is:\n");
	for(i=0;i<sizeof(s);i++)
	    {
		printf("%s",buffer);
		}
	printf("\n");
	dpput(temp,a,-1,buffer,-1,id1);
	
		free(buffer);
	//printf("temp2222 is executed\n");
	//char *dpget(DEPOT *depot, const char *kbuf, int ksiz, int start, int max, int *sp);

    //printf("temp3332 is executed\n");
   //char *fp=dpget(temp,a,sizeof(a),m,100,n);
    //printf("%s\n",dperrmsg(dpecode));
	//printf("data is %s",fp);
	
	//dpout(temp,a,-1);
	//printf("\ndeleted");
	dpclose(temp);
	}
