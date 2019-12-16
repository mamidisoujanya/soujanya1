#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "depot.h"
#define P(X)                                                                  
  X(temparature) \                                                            
  X(humidity)    \                                                            
  X(firestate)  \                                                           
  X(doorlock)

#define f(x) x,
#define g(x) #x,
struct devicedata {
  char name[20];
  char location[20];
  char manufacturer[20];
  int n;
  int lastmodifiedtime;
};
struct dvpair {
  char value[20];
};

enum { P(f) };
char *strings[] = {P(g)};
int adddata() {

  int id, i;
  char *a, newnum[10], key[10];

  DEPOT *temp = dpopen("kkfile", DP_OWRITER | DP_OCREAT | DP_OREADER, -1);
  printf("%s\n", dperrmsg(dpecode));

  a = dpget(temp, "newid", -1, 0, 2, NULL);
  if (a == NULL) {
    sprintf(newnum, "%d", 1);

    if (!dpput(temp, "newid", -1, newnum, 2, id)) {
      printf(" %s\n", dperrmsg(dpecode));
    }
  } else {
    sprintf(newnum, "%d", atoi(a) + 1);

    printf("newid  %s\n", newnum);
    if (!dpput(temp, "newid", -1, newnum, 2, id)) {
      printf(" %s\n", dperrmsg(dpecode));
    }
  }

  struct devicedata s;
  printf("enter name\n");
  scanf("%19s", s.name);
  printf("enter locaion\n");
  while ((getchar()) != '\n');
  scanf("%19s", s.location);
  printf("enter manufacturer\n");
  while ((getchar()) != '\n');
  scanf("%19s", s.manufacturer);
  printf("enter the n value how many device values you want enter\n");
  while ((getchar()) != '\n');
  scanf("%d", &s.n);
  dpput(temp, newnum, -1, (char *)&s, sizeof(struct devicedata), id);
  struct dvpair dp;
  for (i = 0; i < s.n; i++) {
    sprintf(key, "%d.%d", atoi(newnum), i);
    printf("key is%s\n", key);
    printf("enter the  value of");
    printf(" %s\n", strings[i]);
    scanf("%s", dp.value);
    dpput(temp, key, -1, (char *)&dp, sizeof(struct dvpair), id);
  }
  dpclose(temp);
}

int getdata() {

  int i, j;
  char num[10], key[10];
  DEPOT *temp = dpopen("kkfile", DP_OREADER, -1);
  printf("%s\n", dperrmsg(dpecode));
  printf("enter the id\n");
  scanf("%d", &i);
  sprintf(num, "%d", i);
  struct devicedata *g;
  g = (struct devicedata *)dpget(temp, num, -1, 0, sizeof(struct devicedata),NULL);
  printf("%s\n", dperrmsg(dpecode));
  printf("name is :%s\n", g->name);
  printf("location is :%s\n", g->location);
  printf("manufacturer is: %s\n", g->manufacturer);
  printf("lastmodifiedtime %ld\n", dpmtime(temp));
  struct dvpair *dvp;
  for (j = 0; j < g->n; j++) {
    sprintf(key, "%d.%d", atoi(num), j);
    printf("key is%s\n", key);
    dvp = (struct dvpair *)dpget(temp, key, -1, 0, sizeof(struct dvpair), NULL);
    printf("%s\t %s\n", strings[j], dvp->value);
  }
  dpclose(temp);
}

int editdata() {

  int i, k, m, l, id;
  char num[10], key[10];
  printf("enter the id\n");
  scanf("%d", &i);
  sprintf(num, "%d", i);
  printf("enter the k value to edit \n1.for "
         "name\n2.location\n3.manufacture\n4.total change devicedata excluding "
         "values\n5.perticular value\n6.change all values\n7.changes all the "
         "information\n");
  scanf("%d", &k);
  DEPOT *temp = dpopen("kkfile", DP_OWRITER | DP_OCREAT | DP_OREADER, -1);
  printf("%s\n", dperrmsg(dpecode));
  struct devicedata *g;
  struct dvpair *dvp;
  switch (k) {
  case 1:
    g = (struct devicedata *)dpget(temp, num, -1, 0, sizeof(struct devicedata),NULL);
    printf("%s\n", dperrmsg(dpecode));
    printf("enter name\n");
    scanf("%19s", g->name);
    dpput(temp, num, -1, (char *)g, sizeof(struct devicedata), id);
    break;
  case 2:

    printf("%s\n", dperrmsg(dpecode));
    g = (struct devicedata *)dpget(temp, num, -1, 0, sizeof(struct devicedata),NULL);
    printf("enter locaion\n");
    scanf("%19s", g->location);
    dpput(temp, num, -1, (char *)g, sizeof(struct devicedata), id);
    break;
  case 3:

    g = (struct devicedata *)dpget(temp, num, -1, 0, sizeof(struct devicedata),NULL);
    printf("%s\n", dperrmsg(dpecode));
    printf("enter manufacturer\n");
    scanf("%19s", g->manufacturer);
    dpput(temp, num, -1, (char *)g, sizeof(struct devicedata), id);
    break;
  case 4:
    g = (struct devicedata *)dpget(temp, num, -1, 0, sizeof(struct devicedata),NULL);
    printf("%s\n", dperrmsg(dpecode));
    printf("enter name\n");
    scanf("%19s", g->name);
    printf("enter locaion\n");
    while ((getchar()) != '\n');
    scanf("%19s", g->location);
    printf("enter manufacturer\n");
    while ((getchar()) != '\n');
    scanf("%19s", g->manufacturer);
    dpput(temp, num, -1, (char *)g, sizeof(struct devicedata), id);
    break;
  case 5:
    printf("enter the index \n0.for temparature\n1.humidity\n2.firestate\n");
    scanf("%d", &m);
    sprintf(key, "%d.%d", atoi(num), m);
    printf("key is%s\n", key);
    dvp = (struct dvpair *)dpget(temp, key, -1, 0, sizeof(struct dvpair), NULL);
    printf("%s\n", dperrmsg(dpecode));
    printf("enter the value of %s\n", strings[m]);
    scanf("%s", dvp->value);
    dpput(temp, key, -1, (char *)dvp, sizeof(struct dvpair), id);
    break;
  case 6:

    g = (struct devicedata *)dpget(temp, num, -1, 0, sizeof(struct devicedata),NULL);
    printf("%s\n", dperrmsg(dpecode));
    printf("n is :%d\n", g->n);
    for (l = 0; l < g->n; l++) {
      sprintf(key, "%d.%d", atoi(num), l);
      dvp =(struct dvpair *)dpget(temp, key, -1, 0, sizeof(struct dvpair), NULL);
      printf("%s\n", dperrmsg(dpecode));
      printf("key is%s\n", key);
      printf("enter the  value of");
      printf("%s\n", strings[l]);
      scanf("%s", dvp->value);
      dpput(temp, key, -1, (char *)dvp, sizeof(struct dvpair), id);
    }
    break;
  case 7:
    g = (struct devicedata *)dpget(temp, num, -1, 0, sizeof(struct devicedata),NULL);
    printf("%s\n", dperrmsg(dpecode));
    printf("enter name\n");
    scanf("%19s", g->name);
    printf("enter locaion\n");
    while ((getchar()) != '\n');
    scanf("%19s", g->location);
    printf("enter manufacturer\n");
    while ((getchar()) != '\n');
    scanf("%19s", g->manufacturer);
    dpput(temp, num, -1, (char *)g, sizeof(struct devicedata), id);
    printf("n is :%d\n", g->n);
    for (l = 0; l < g->n; l++) {
      sprintf(key, "%d.%d", atoi(num), l);
      dvp =(struct dvpair *)dpget(temp, key, -1, 0, sizeof(struct dvpair), NULL);
      printf("%s\n", dperrmsg(dpecode));
      printf("key is%s\n", key);
      printf("enter the  value of");
      printf("%s\n", strings[l]);
      scanf("%s", dvp->value);
      dpput(temp, key, -1, (char *)dvp, sizeof(struct dvpair), id);
    }
    break;
  }
  dpclose(temp);
}

int deletedata() {

  int l, i, id;
  char num[10], key[10];
  printf("enter the id\n");
  scanf("%d", &i);
  sprintf(num, "%d", i);
  struct devicedata *g;
  DEPOT *temp = dpopen("kkfile", DP_OWRITER | DP_OCREAT | DP_OREADER, -1);
  printf("%s\n", dperrmsg(dpecode));
  g = (struct devicedata *)dpget(temp, num, -1, 0, sizeof(struct devicedata),NULL);
  printf("%s\n", dperrmsg(dpecode));
  dpout(temp, num, -1);
  printf("%s\n", dperrmsg(dpecode));
  for (l = 0; l < g->n; l++) {
    sprintf(key, "%d.%d", atoi(num), l);
    dpout(temp, key, -1);
    printf("%s\n", dperrmsg(dpecode));
  }
  dpclose(temp);
}
int main() {

  int i;
  printf("**********menu*********");
  printf("enter the choice\nn1.foradddata\n2.getdata\n3.editdata\n4.deletedata");
  scanf("%d", &i);
  if (i == 1) {
    adddata();
  } else if (i == 2) {
    getdata();
  } else if (i == 3) {
    editdata();
  } else if (i == 4) {
    deletedata();
  }
}
