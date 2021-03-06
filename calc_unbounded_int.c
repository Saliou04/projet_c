#include "unbounded_int.c"

#define LEN 1024


struct my_list{
  struct my_list *suivant;
  char *nom;
  unbounded_int valeur;
};

typedef struct my_list my_list;
typedef my_list *liste;
liste l=NULL;
liste creer_liste(char * nom, unbounded_int v){
  liste first=malloc(sizeof(my_list));
  if(first==NULL){
    return NULL;
  }
  first->suivant=NULL;
  first->valeur=v;
  first->nom=nom;
  return first;
}
int compare(char *a,char *b){
  int n=strcmp(a,b);
  if(n==0){
    return 0;
  }else{
    return -1;
  }
}
liste insertion(liste l, char *nom, unbounded_int v){
  if(l==NULL){
    l=creer_liste(nom,v);
  }else if(compare(l->nom,nom)==0){
      l->valeur=v;
  }else{
    l->suivant=insertion(l->suivant,nom,v);
  }
  return l;  
}
void afficher_liste(liste l){
  liste a=l;
  while(a!=NULL){
    printf("%s\n",a->nom);
    afficher_unb(a->valeur);
    a=a->suivant;
  }
}
char * suprimer_espace(char * str){
  int i = 0, j = 0;
  char * res=malloc(sizeof(strlen(str)+1));
  if(res==NULL){
    return NULL;
  }
  while (str[i]!='\0'){
    // printf("%c \n" , str[i]);
    if (str[i] != ' '){
      res[j] = str[i];
      j+=1;
    }
    i++;
  }
  res[j] = '\0';
  //free(str);
  return res;
}

unbounded_int get_liste(liste l, char *a){
  liste b=l;
  while(b!=NULL){
    if(compare(a,b->nom)==0){
      return b->valeur;
    }else{
      b=b->suivant;
    }
  }
  return  string2unbounded_int("0");
}
int est_printf(char *tab){
  char *s="print";
  for(int i=0;i<5;i++){
    if(tab[i]!=s[i]){
      return -1;
    }
  }
  return 0;
}
unbounded_int variable(char *a){
  if(a[0]=='-' || a[0]=='+' || isdigit(a[0])){
    return  string2unbounded_int(a);
  }else{
    return get_liste(l,a);
  }
}
unbounded_int operation(char op,unbounded_int val1,unbounded_int val2){
  if(op=='+' ){
    return  unbounded_int_somme(val1,val2);
  }else if (op=='-'){
       return unbounded_int_difference(val1,val2);
 }else{	      
    return  unbounded_int_produit(val1,val2);
  }  
}

void afficher_chiffre_flo(chiffre *x,FILE *fr){
  if(x == NULL){
    fprintf(fr,"\n");
    return ;
  }
  fprintf(fr,"%c", x->c);
  afficher_chiffre_flo(x->suivant,fr);
}
void afficher_unbou_flo(unbounded_int x,FILE *fr){
  
  fprintf(fr," %c ",x.signe);
  // printf("TAILLE:    %ld\n",x.len);

  afficher_chiffre_flo(x.premier,fr);
  //fprintf(fr,"\n");
 }
void funct(char *fic, char *dest){
  FILE *src=fopen(fic,"r");
  if(src==NULL){
    return;
  }
  FILE *fw = dest != NULL ? fopen(dest, "w") :stdout;
  char *line_file=malloc(LEN);
  if(line_file==NULL){
    return ;
  }
  char somme='+';
  char soustraction='-';
  char produit='*';
  char res;
  int i;
  int j;
  int k;
  unbounded_int val1;
  unbounded_int val2;
  while( fgets(line_file , LEN , src)!=NULL ) {
    i=0;
    j=0;
    k=0;
    line_file=suprimer_espace(line_file);
    //int n=strlen(line_file)+1;
    char * nom_var= malloc(LEN);
    char *valeur_var= malloc(LEN);
    char *valeur_var2= malloc(LEN);
    if(nom_var==NULL || valeur_var==NULL || valeur_var2==NULL){
      printf("%s \n", "NULL");
      return ;
    }
    if(line_file[i]=='\0' || line_file[i]=='\n'){
      continue;
    }
   else if(est_printf(line_file)==0){
      i+=5;//taille de print
       while(line_file[i] != '=' && line_file[i] != '\n' && line_file[i]!='\0'){
	  nom_var[i-5]= line_file[i];
	  i++;
       }
      
       fprintf(fw,"%s = ",nom_var);
     
       afficher_unbou_flo(get_liste(l,nom_var),fw);
      
    }else {

      //NOMS DE VARIABLE ()
      while(line_file[i] != '=' && line_file[i] != '\n' && line_file[i]!='\0'){
	  nom_var[i]= line_file[i];
	  i++;
      }
      // printf("%s\n",nom_var);
      if(line_file[i] == '\n' || line_file[i]=='\0') {
	printf("arumet defalte\n");
	return ;
     }
      //PREMIER VALEUR ENTRE '=' ET L'OP
       if(line_file[i] == '='){
	  i+=1;
    	 
	  valeur_var[j]=line_file[i];
	  i+=1;
	  j+=1;
	  
	  while(line_file[i]!='\n' && line_file[i]!='\0' && line_file[i] != somme && line_file[i] !=soustraction  && line_file[i] != produit ){
	    valeur_var[j] = line_file[i];
	        	j++;
		       i++;
	  }
	  if(line_file[i] == somme || line_file[i] ==soustraction  || line_file[i] == produit ){
		// if( op (somme , soustraction , produit) == line_file[i+1])
		  res=line_file[i];
		  i+=1;
		  
		  while(line_file[i]!='\n' && line_file[i]!='\0'){
		    valeur_var2[k]= line_file[i];
		    i++;
		    k++;
		  }	 
		  val1=variable(valeur_var);
		  val2=variable(valeur_var2);

		  unbounded_int c=operation(res,val1,val2);
		  l=insertion(l,nom_var,c);  
    
	  }else if(valeur_var[0]=='-' || valeur_var[0]=='+' || isdigit(valeur_var[0])){
	      l=insertion(l,nom_var,string2unbounded_int(valeur_var));
	  }else{
	      l=insertion(l,nom_var,get_liste(l,valeur_var));
	  }
	  
	     	 
      }else{
	//gerer le cas ou i n''y pas d'affectation
	perror("argument defalte\n");
	return;
      }
    }
    //free(nom_var);
     // free(nom_var);
    // free(valeur_var);
     //free(valeur_var);
     // free(valeur_var2);
     //free(valeur_var2);
  }
  //  afficher_liste(l);
  fclose(src);
  fclose(fw);
}


int main(int argc, char **argv){
  funct("/home/saliou/Cour/2021/C/projet/p2/projet_c/tex.txt",NULL);
  
  return 0;
}
