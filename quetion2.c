#include "depot.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct devicedata {

  char name[20];
  char location[20];
  char manufacturer[20];
  int lastmodifiedtime;
};
struct dvPair {
  int id;
  char value[20];
};

int adddata() {

  int id1;
  int *n, i, id, id2;
  char *buffer, newnum[10];
  char *a, *b;

  buffer = (char *)malloc(100 * sizeof(char));
  DEPOT *temp = dpopen("llfile", DP_OWRITER | DP_OCREAT | DP_OREADER, -1);
  printf("%s\n", dperrmsg(dpecode));

  a = dpget(temp, "newid", -1, 0, 10, NULL);
  if (a == NULL) {
    sprintf(newnum, "%d", 1);
    a = newnum;
    printf("new %s\n", a);
    if (!dpput(temp, "newid", -1, newnum, 10, id)) {
      printf(" %s\n", dperrmsg(dpecode));
    }
  } else {
    sprintf(newnum, "%d", atoi(a) + 1);
    a = newnum;
    printf("newid  %s\n", a);
    if (!dpput(temp, "newid", -1, newnum, 10, id)) {
      printf(" %s\n", dperrmsg(dpecode));
    }
  }

  struct devicedata s;
  printf("enter name\n");
  scanf("%s", name);
  printf("enter locaion\n");
  scanf("%s", s.location);
  printf("enter manufacturer\n");
  scanf("%s", s.manufacturer);
  // memcpy(buffer, &s, 100);

  // for (i = 0; i < sizeof(s); i++) {
  //  printf(" %02x", buffer[i]);
  //  }

  dpput(temp, a, -1, name, sizeof(name), id1);

  dpclose(temp);
}

int getdata() {

  int *n, i, j;
  char *a, *fp, b[10], name[20];
  DEPOT *temp = dpopen("llfile", DP_OREADER, -1);
  printf("%s\n", dperrmsg(dpecode));

  printf("enter the id\n");
  scanf("%d", &i);
  a = (char *)&i;
  printf("id is: %d\n", *a);

  struct devicedata *g;
  fp = dpget(temp, a, -1, 0, -1, n);
  g = (struct devicedata *)fp;

  printf("name is :%s", fp);
  printf("location is :%s\n", g->location);
  printf("manufacturer is: %s\n", g->manufacturer);
  printf("lastmodifiedtime %ld", dpmtime(temp));

  dpclose(temp);
}

int editdata() {

  int i;
  printf("enter the i value to edit \n1.for "
         "name\n2.location\n3.manufacture\n4.value");
  scanf("%d", &i);
  struct devicedata s;
  switch (i) {
  case 1:

    printf("enter name\n");
    scanf("%s", s.name);
    break;
  case 2:
    printf("enter locaion\n");
    scanf("%s", s.location);
    break;
  case 3:
    printf("enter manufacturer\n");
    scanf("%s", s.manufacturer);
    break;
  case 4:
    printf("enter the value\n");
    // scanf("%s",v.value);
    break;
  }
}
int deletedata() {
  int *n;
  char c;
  c = 'x';
  const char *a = "abcd";

  DEPOT *temp = dpopen("llfile", DP_OREADER, 100);
  printf("%s\n", dperrmsg(dpecode));
  printf("temp is executed\n");
  if (temp == NULL) {
    printf("temp is null\n");
  } else {
    printf("sucess\n");
  }
  dpout(temp, a, sizeof(a));
  dpclose(temp);
}
int main() {

  int i;
  // printf("**********menu*********");

  printf(
      "enter the choice\n "); //\n1.for
                              // adddata\n2.getdata\n3.editdata\n4.deletedata");
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
