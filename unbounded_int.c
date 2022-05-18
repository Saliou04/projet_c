
#include <stdlib.h>
#include "unbounded_int.h"

#include<stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include <math.h>


chiffre * creer_chiffre(chiffre *pre,char c,chiffre * suiv){
  chiffre * x=malloc(sizeof(chiffre));
  if(x == NULL ) return x;
  x->c = c;
  x->suivant = suiv;
  x->precedent = pre;
  return x;
}


void afficher(chiffre *x){
  if(x == NULL){
    printf("\n");
    return ;
  }
  printf("%c", x->c);
    afficher(x->suivant);
}

//Cette fonction permet d'ajouter un chiffre au debut d'un autre
chiffre * ajouter_debut(chiffre * x, char c){
  chiffre *y=creer_chiffre(NULL,c,x); //creation du chiffre 
  if(x!=NULL){      //cr22ation de la liaison avec le chiffre x
    x->precedent=y; 
  }
  return y;
}
//ajouter le chiffre c a la fin d'une chiffre x
chiffre *ajouter_fin(chiffre * x, char c){
  chiffre *y = creer_chiffre( x , c , NULL);
 if(x != NULL){
   x->suivant = y;
 }
  return y;
}

chiffre * ajouter_chiffre(chiffre *x, char c){
  if(x == NULL) return creer_chiffre( NULL, c , NULL);
   else if(x->suivant == NULL){
    x->suivant= creer_chiffre( x , c , NULL);
    return x;
   }
   x->suivant=ajouter_chiffre(x->suivant,c);
   return x;
}



unbounded_int string2unbounded_int(const char *e){
   unbounded_int x;
   x.len=0;
   int i=0;  
  if(e[0]=='+' || e[0]=='-'){
    x.signe=e[0];
    i=1;
  } else if(isdigit(e[0])){
      x.signe='+';
  }
  while(e[i]=='0' && e[i+1]!='\0'){
    i++; 
  }
   if(isdigit(e[i])){
       x.premier=ajouter_fin(NULL,e[i]);
       x.dernier=x.premier;
       x.len+=1;
   }else{
       x.signe='*';
      return x;
  }
  for (int j=i+1;e[j]!='\0';j++){
    if(isdigit(e[j])){
      x.dernier->suivant=ajouter_fin(x.dernier,e[j]);
      x.dernier=x.dernier->suivant;
      x.len+=1;
    }else{
      x.signe='*';
      return x;
    }
  }
  return x;
  
}


void afficher_unb(unbounded_int x){
  
   printf("signe: %c\n",x.signe);
  printf("TAILLE:    %ld\n",x.len);

   afficher(x.premier);
   printf("\n");
}


unbounded_int ll2unbounded_int(long long i){
  /*double x=log(i)+1;
  char str[(int )x];
  sprintf(str,"%lld",i);
  return string2unbounded_int(str);*/
   unbounded_int x;
  if(i<0){
    x.signe='-';
    i=(-1)*i;
  }else{
    x.signe='+';
  }
  int r=i%10;
  i=i/10;
  x.premier=creer_chiffre(NULL,((char)(r+'0')),NULL);
  
  x.dernier=x.premier;
  x.len=1;
  while(i!=0){
    r=i%10;
    i =i/10;
    x.premier=ajouter_debut(x.premier,((char)(r+'0')));

    x.len+=1;
  }
  return x;
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
    j+=1;
  }
   tab[x-1]='\0';
   return &tab[0];
}


int unbounded_int_cmp_unbounded_int(unbounded_int a, unbounded_int b){
  //return -1 si a<b;
  //0 si a==b; 1 si a>b
  if(a.len==1 && a.premier->c=='0'){
    a.signe='+';
  }
  if(b.len==1 && b.premier->c=='0'){
    a.signe='+';
  }
  
  if(a.signe=='+' && b.signe=='-') return 1;
  if(a.signe=='-' && b.signe=='+') return -1;
  if(a.len!=b.len){
    if( a.signe=='+'){
      return (a.len <b.len) ? -1: 1;
    }else{
       return (a.len >b.len) ? -1: 1;
    }
  }
  chiffre * a1=a.premier;
  chiffre * a2=b.premier;
  while(a1!=NULL){
    if(a1->c> a2->c) {
      return (a.signe=='+')? 1:-1;
    }if(a1->c < a2->c) {
      return (a.signe=='+')? -1: 1;
    }
    a1=a1->suivant;
    a2=a2->suivant;
  }
  return 0;
}
long long transform_int(unbounded_int a){
  long long i=0;
  chiffre * aux=a.premier;
  while(aux!=NULL){
    i=i*10+(aux->c-'0');
    aux=aux->suivant;
  }
  return (a.signe=='+')? i:-i;
}
int unbounded_int_cmp_ll(unbounded_int a, long long b){
   //return -1 si a<b;
  //0 si a==b; 1 si a>b
  // char c= b>=0 ? '+':'-';
  if(a.signe=='+' && b <0){
    return 1;
  }
  if(a.signe=='-' && b>0){
    return -1;
  }
  long long i=transform_int(a);
  if(i==b) return 0;
  return (i<b)? -1: 1;
}

unbounded_int somme(unbounded_int a, unbounded_int b){
  unbounded_int res;
  res.signe='+';
  chiffre *a1=a.dernier;
  chiffre * a2=b.dernier;
  int i=(a1->c -'0')+(a2->c-'0');
  res.dernier= creer_chiffre(NULL,(char)((i%10)+'0'),NULL);
  res.premier=res.dernier;
  a1=a1->precedent;
  a2=a2->precedent;
  res.len=1;
  while(a1!=NULL || a2!=NULL){
    if(a1!=NULL && a2!=NULL){
      i=(i/10)+(a1->c -'0')+(a2->c-'0');
       a1= a1->precedent;
       a2=a2->precedent;
    }else if(a1!=NULL){
      i=(i/10)+(a1->c-'0');
      a1= a1->precedent;
    }else{
       i=(i/10)+(a2->c-'0');
       a2=a2->precedent;
    }
     res.premier->precedent=ajouter_debut(res.premier,(char)((i%10)+'0'));
     res.premier=res.premier->precedent;
     res.len+=1;
  }
   
  return res;
}
unbounded_int diff(unbounded_int a, unbounded_int b){
  unbounded_int res;
  res.signe='+';
  chiffre *a1=a.dernier;
  chiffre * a2=b.dernier;
  int r=0;
  int i=(a1->c -'0')-(a2->c-'0')+r;
  if(i<0){
    i+=10;
    r=-1;
  }else{
    r=0;
  }
  res.dernier= creer_chiffre(NULL,(char)(i+'0'),NULL);
  res.premier=res.dernier;
  a1=a1->precedent;
  a2=a2->precedent;
  res.len=1;
  while(a1!=NULL || a2!=NULL){
    if(a1!=NULL && a2!=NULL){
      i=r+(a1->c -'0')-(a2->c-'0');
       a1= a1->precedent;
       a2=a2->precedent;
    }else{
      i=r+(a1->c-'0');
      a1= a1->precedent;
    }
    if(i<0){
      i+=10;
      r=-1;
    }else{
      r=0;
    }
    
     res.premier->precedent=ajouter_debut(res.premier,(char)(i+'0'));
     res.premier=res.premier->precedent;
     res.len+=1;
  }
   
  return res;
}

unbounded_int unbounded_int_somme(unbounded_int a, unbounded_int b){
   unbounded_int res;
   // la deux sont de meme signe positif
  if(a.signe=='+' && b.signe=='+'){
    res=somme(a,b);
    
  }//les deuxx sont negatif
  else if(a.signe=='-' && b.signe=='-'){
    res=somme(a,b);
    res.signe='-';
    return res;
  }// les deux sont de signes distingue 
  else {
    char c1=a.signe;// je stock les signes
    char c2=b.signe;
    //je calcule les valeurs absolue
    if(c1=='-'){ 
      a.signe='+';
    }if(c2=='-'){
      b.signe='+';
    }
    // si |a|>|b|; a+b=a-|b|
    if(unbounded_int_cmp_unbounded_int(a,b)==1){
      res=diff(a,b);
      res.signe=c1;
      //si |a|<|b| ; a+b=b-|a|
    }else if(unbounded_int_cmp_unbounded_int(a,b)==-1){
	res=diff(b,a);
	res.signe=c2;
	// |a|=|b| donc a+b=0
    }else{
     
      res.signe='+';
      res.len=1;
      res.premier=creer_chiffre(NULL,'0',NULL);
      res.dernier=res.premier;
    }
    // je remet les bon signe pour ne pasmodifier les structure
    //de base
    a.signe=c1;
    b.signe=c2;
  }
    return res;
  
}
unbounded_int unbounded_int_difference( unbounded_int a, unbounded_int b){
  char c=b.signe;
  if(b.signe=='+'){
    b.signe='-';
  }else{
    b.signe='+';
  }
  unbounded_int res=unbounded_int_somme(a,b);
  b.signe=c;
  return res;
}

unbounded_int unbounded_int_produit(unbounded_int a, unbounded_int b){
  //longueur de c et alloccation d'une memoire capable de
  //recevoir le resultat
  int n=a.len+b.len;
  char *c=malloc(n+1);
  /*trasformation dess nombre en chaine de caractere et
   *positionnement du pointeur a la fin de la chaine 
   * afin de pouvoir apliquer l'algo de multiplication 
   * utilisation sur papier
   */ 
  char *aa=unbounded_int2string(a)+a.len;
  char *bb=unbounded_int2string(b)+b.len;
 
  //initialisation de tous les valeur a 0
  for(int i=0;i<n+1;i++){
    c[i]='0';
  }
     
  for(int j =0;j<b.len;j++){ //parcour de la chaine b
    int r=0;                //initialisation du retune a 0
    if(bb[j]=='0')  //decalage pour les caractere qui vallent 0
      continue;
    
    for(int i=0;i<a.len;i++){ //parcour de la chaine de a
      //calcule de la valeur a plac2 sur la bonne place
      int v=(c[n-(i+j+1)]-'0')+(aa[-i]-'0')*(bb[-j]-'0')+r;
      c[n-(i+j+1)]=(char)(v%10+'0');
      r=v/10;
    }
    //ajouter le retenue dans la bonne place
    c[n-(j+a.len+1)]=(char)(r+'0');
  }
  //determination du signe du resultats
  if(a.signe==b.signe){
    c[0]='+';
  }else{
    c[0]='-';
  }
  c[n]='\0';// mettre la caractere null pour mettre la fin de la chaine
 
  //transformation de la chaine obtenue en unbounded_int

 return  string2unbounded_int(c);
}

