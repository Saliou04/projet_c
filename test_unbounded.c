

#include "unbounded_int.c"
void test(){
  printf("***************Test des fonction des fonction *********************\n");
  printf("\n**********Transformation d'une chaine en unbounded_int***********\n");
  char *c="1234";
  unbounded_int k=string2unbounded_int(c);
  printf("\n******************charactere c :*****************************\n \n%s",c);
  printf("\n\n*******************L'Unbounded_int ******************************* k\n");
  afficher_unb(k);
  printf("\n**************Transformation de long en unbounded_int**************\n");
  long long i=123456789;
  printf("i : %lld\n",i);
  unbounded_int list =ll2unbounded_int(i);
  printf("\n*******************L'Unbounded_int ******************************* list\n");
  afficher_unb(list);
  printf("\n*********************comarasaison k et list********************************** \n");
  printf("%d\n",unbounded_int_cmp_unbounded_int(k,list));
   printf("\n*********************comarasaison k et et i********************************** \n");
    printf("%d\n",unbounded_int_cmp_ll(k,i));
     printf("\n********************somme de  k et  list********************************** \n");
      unbounded_int a=somme(k,list);
  afficher_unb(a);
   printf("\n********************difference de  list et  k********************************** \n");
   unbounded_int b=diff(list,k);
  afficher_unb(b);
   printf("\n********************produit de  k et  list********************************** \n");
    unbounded_int prod=unbounded_int_produit(list,k);
  afficher_unb(prod);
     
}
int main(){
  test();
   return 0;
}
