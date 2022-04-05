#include "unbounded_int.h"
#include <stdlib.h>
#include<stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include <math.h>
chiffre * creer_chiffre(chiffre *pre,char c,chiffre * suiv){
  chiffre * x=malloc(sizeof(chiffre));
  if(x==NULL) return x;
  x->c=c;
  x->suivant=suiv;
  x->precedent=pre;
  return x;
}
void afficher(chiffre *x){
  if(x==NULL){
    printf("\n");
    return ;
  }
    printf("%c", x->c);
    afficher(x->suivant);
}
chiffre * ajouter_chiffre(chiffre *x, char c){
  if(x==NULL) return creer_chiffre(NULL,c,NULL);
  else if(x->suivant==NULL){
    x->suivant=creer_chiffre(x,c,NULL);
    return x;
  }
  x->suivant=ajouter_chiffre(x->suivant,c);
  return x;
}
   
unbounded_int string2unbounded_int(const char *e){
  unbounded_int x;
  int i=0;
  x.len = strlen(e);
  if(e[0]=='+' || e[0]=='-'){
    x.signe=e[0];
    i=1;
  }else if(isdigit(e[0])){
      x.signe='+';
  }
  x.premier=malloc(sizeof(chiffre));
  x.len -= i;
  for (int j=i;e[j]!='\0';j++){
    if(isdigit(e[j])){
      x.premier=ajouter_chiffre(x.premier,e[j]);
      
    }else{
      x.signe='*';
      return x;
    }
  }
  chiffre *c=x.premier;
  if(c==NULL){
    x.dernier=NULL;
  }
  while(c->suivant!=NULL){
    c=c->suivant;
  }
  x.dernier=c;
  return x;
}
void afficher_unb(unbounded_int x){
  
  printf("signe: %c\n",x.signe);
  printf("TAILLE: % d\n",x.len);
   afficher(x.premier);
  printf("\n");
}
unbounded_int ll2unbounded_int(long long i){
  double x=log(i)+1;
  char str[(int )x];
  sprintf(str,"%lld",i);
    return string2unbounded_int(str);
}
char * unbounded_int2string(unbounded_int i){
  int x=i.len+2;
  char *tab =malloc(x);
  if(tab==NULL) return NULL;
  tab[0]=i.signe;
 
  chiffre * aux=i.premier;
  int j=1;
  while(aux!=NULL){
    tab[j]=aux->c;
    aux=aux->suivant;
    // printf("%c",tab[j]);
    j+=1;
  }
   tab[j+1]='\0';
   return tab;
}
int main(){
  chiffre *x=creer_chiffre(NULL,'1',NULL);
  ajouter_chiffre(x,'2');
   ajouter_chiffre(x,'2');
    ajouter_chiffre(x,'2');
     ajouter_chiffre(x,'2');
     /// afficher(x);
   printf("\n");
  char * c="1234";
  unbounded_int k=string2unbounded_int(c);
  //unbounded_int k={'+',4,x,x->suivant->suivant->suivant->suivant};
  //afficher_unb(k);
  unbounded_int list =ll2unbounded_int(123456789);
  // afficher_unb(list);
  //afficher(list.dernier);
    char *ca=unbounded_int2string(list);
    for(int i=1; ca[i]!='\0';i++){
    printf("%c",ca[i]);
  }
  printf("\n");
  return 0;
}
