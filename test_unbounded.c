

#include "unbounded_int.c"
int main(){
  chiffre *x=creer_chiffre(NULL,'1',NULL);
  ajouter_chiffre(x,'2');
   ajouter_chiffre(x,'2');
    ajouter_chiffre(x,'2');
     ajouter_chiffre(x,'2');
   printf("transform cer en u\n");
  char * c="-1234";
   unbounded_int k=string2unbounded_int(c);
 
  afficher_unb(k);
  printf("trabs ll i\n");
 
  unbounded_int list =ll2unbounded_int(123456789);
  afficher_unb(list);
  
  char *ca=unbounded_int2string(list);
   
  printf("car * %s\n",ca);
  printf("compa\n");
  printf("%d\n",unbounded_int_cmp_unbounded_int(k,list));
  printf("%d\n",unbounded_int_cmp_ll(k,123456789));
  printf("\n Somme \n");
  unbounded_int a=somme(k,list);
  afficher_unb(a);
   unbounded_int b=diff(list,k);
  printf("\n **********dif******* \n ");
  afficher_unb(b);
  unbounded_int som= unbounded_int_difference(list,k);
  printf("\n ****************dif lis*********\n");
  afficher_unb(som);
  printf("\n *********produit****\n");
  unbounded_int prod=unbounded_int_produit(list,k);
  affiche(prod);
   return 0;
}
