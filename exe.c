#include <stdlib.h>
//#include "unbounded_int.h"

#include<stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include <math.h>


int main(){
  char * a="21";
  char *b="15";
  char *c=malloc(5);
  for(int a=0;a<5;a++){
    c[a]=(char)(0+'0');
  }
  for(int i =0;i<2;i++){
    int r=0;
    if(b[i]-'0'==0)
      continue;
    for(int j=0;j<2;j++){
      int v=(c[i+j]-'0')+(a[j]-'0')*(b[i]-'0')+r;
      c[i+j]=v%10;
      r=v/10;
    }
    c[i+2]=r;
  }

  printf("produit : %s\n", c);
  return 0;
}
