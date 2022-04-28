

void interprete(char *source, char *sorti ){
  unbounded_int * tab[26];
  char op;
  FILE *fr= source!=NULL ? fopen(source, "r") : stdin;
  if(fr==NULL){
    exit(1);
  }

  FILE *fw = sortie!=NULL ? fopen(sortie,"w") :stdout;
  if(fw==NULL){
    fclose(fr);
  }


  /* int c;
  char k;
  int i=0;
  char *variable; 
  while(fscanf(fr,"%c",&k)==1){
    if(k!=27){
      variable[i++]=k;
      k++;
      }*/
  char *ligne[1024];
  while(fgets(tab,1024,fr)!=NULL){
    char *chifre[1];
    int i;
    int j=0;
    for( i=2;(ligne[i]!='\0' && ligne[i]!=' ' );i++){ 
      chifre[j++]=ligne[i];
    }
    op=tab[i];
    
}
