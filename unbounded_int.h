typedef struct chiffre{
  struct chiffre *suivant;
  char c;
  struct chiffre *precedent;
} chiffre;
typedef struct{
  char signe; /* soit ’+’ soit ’-’ */
  //size_t
  int len; /*longueur de la liste */

  chiffre *premier; /* pointeur vers le premier élément de la liste*/
  chiffre *dernier;/*pointeur vers le dernier élément de la liste*/
} unbounded_int;
/* cette fonction prend en argument l'adresse d'une chaine de chaine 
 * de caracteres et rnvoyant une valeur unbounded_int
 */
/*
Cette fonction prend en parametre un chaine de caractere et renvoi un unbound

 */
unbounded_int string2unbounded_int(const char *e);
//prendre un entier et renvoyer un unbou
unbounded_int ll2unbounded_int(long long i);

char *unbounded_int2string(unbounded_int i);

int unbounded_int_cmp_unbounded_int(unbounded_int a, unbounded_int b);

int unbounded_int_cmp_ll(unbounded_int a, long long b);


unbounded_int unbounded_int_somme(unbounded_int a, unbounded_int b);


unbounded_int unbounded_int_difference( unbounded_int a, unbounded_int b);
unbounded_int unbounded_int_produit( unbounded_int a, unbounded_int b);



