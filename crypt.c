#include "crypt.h"

/* ------------------------------------------------------
 * decypher
 */
void decypher(char* key,char* keyTab,char * from, char * to){
  unsigned char* tab=generateTab(keyTab);
  int i, j;
  int idLast;
  char * text = NULL, *text_tmp = NULL;
  FILE * fp;
  unsigned newRandom;

  if(from && to && key && keyTab){
    fp=fopen(from,"r");
    text_tmp=read_str(fp,&idLast,EOF);
    fclose(fp);
    idLast--;

    i=0;
    j=0;
    newRandom=(tab[0]=='\n'?0:tab[0]-FIRSTCHAR-1);
    text=malloc((strlen(text_tmp)+1)*sizeof(*text));
    while(idLast>-1 && text_tmp[i]){
      if(!newRandom){
	newRandom=(tab[text_tmp[i]%SIZE]=='\n'?0:tab[text_tmp[i]%SIZE]-FIRSTCHAR-1);
	--idLast;
	i++;
      }else{
	newRandom--;
      }
      text[j]=text_tmp[i];
      ++j;
      ++i;
    }
    text[j]=0;
    
    i=0;
    while(key[i]){
      ++i;
    }
    --i;
    if(i>-1 && idLast>-1){
      while(i){
	if(key[i]>FIRSTCHAR && key[i]<=LASTCHAR){
	  applyDecypher(text,key[i],tab,idLast);
	}
	--i;
      }

      if(key[0]>FIRSTCHAR && key[0]<=LASTCHAR){
	applyDecypher(text,key[0],tab,idLast);
      }

      /*sauvegarde*/
      fp=fopen(to,"w");
      if(fp){
	reverse(text);
	fputs(text,fp);
	fclose(fp);
      }
    }
  }

  if(text){
    free(text);
  }
  if(text_tmp){
    free(text_tmp);
  }
}

void applyDecypher(char * text,char ch,unsigned char* tab,int idLast){
  int id=0;

  if(text && tab){
    while(idLast){
      id=find(tab,text[idLast]);
      if(id!=-1){
	id-=(text[idLast-1]=='\n'?0:text[idLast-1]-FIRSTCHAR);
	if(id<0){
	  id+=SIZE;
	}
	text[idLast]=tab[id];
      }
      idLast--;
    }
    id=find(tab,text[0]);
    if(id>=0 && id<SIZE){
      id-=(ch=='\n'?0:ch-FIRSTCHAR);
      if(id<0){
	id+=SIZE;
      }
      text[0]=tab[id];
    }
  }
}
/* ------------------------------------------------------ */



/* ------------------------------------------------------
 * cypher
 */
void cypher(char* key, char* keyTab,char * from, char * to){
  unsigned char* tab=generateTab(keyTab);
  int i, j;
  char * text_tmp=NULL, *text=NULL;
  FILE * fp;
  unsigned newRandom, count;

  if(key && keyTab && tab && from && to){
    fp=fopen(from,"r");
    text_tmp=read_str(fp,NULL,EOF);
    reverse(text_tmp);
    fclose(fp);
    
    i=0;
    while(key[i]){
      if(key[i]>FIRSTCHAR && key[i]<=LASTCHAR){
	applyCypher(text_tmp,key[i],tab);
      }
      ++i;
    }

    count = strlen(text_tmp);
    text=malloc((count*2+1)*sizeof(*text));
    i=0;
    j=0;
    newRandom=(tab[0]=='\n'?0:tab[0]-FIRSTCHAR-1);
    while(text_tmp[i]){
      if(count){
	if(!newRandom){
	  count--;
	  text[j]=tab[rand()%SIZE];
	  newRandom=(tab[text[j]%SIZE]=='\n'?0:tab[text[j]%SIZE]-FIRSTCHAR-1);
	  ++j;
	}else{
	  newRandom--;
	}
      }
      text[j]=text_tmp[i];
      ++i;
      ++j;
    }
    text[j]=0;

    /* sauvegarde */
    fp=fopen(to,"w");
    if(fp){
      fputs(text,fp);
      fclose(fp);
    }
  }

  if(text){
    free(text);
  }
  if(text_tmp){
    free(text_tmp);
  }
}

void applyCypher(char* text,char c,unsigned char* tab){
  int i=0,id;
  unsigned char last=(c=='\n'?0:c-FIRSTCHAR);

  while(text[i]){
    id=find(tab,text[i]);
    if(id>=0 && id<SIZE){
      id=(id+last)%SIZE;
      text[i]=tab[id];
      last=(text[i]=='\n'?0:text[i]-FIRSTCHAR);
    }
    ++i;
  }
}
/* ------------------------------------------------------ */



/* ------------------------------------------------------
 * tab
 */
unsigned char* generateTab(char* key){
  unsigned char *tab=malloc(SIZE*sizeof(*tab));
  int i=0;

  for(i=0;i<SIZE;++i){
    tab[i]=FIRSTCHAR+i;
  }

  i=0;
  while(key[i]){
    if(key[i]>FIRSTCHAR && key[i]<=LASTCHAR){
      shuffle(tab,key[i]);
    }
    ++i;
  }

  for(i=0;i<SIZE;++i){
    if(tab[i]==FIRSTCHAR){
      tab[i]='\n';
    }
  }
  
  return tab;
}

void shuffle(unsigned char *tab,char c){
  char used[SIZE];
  int i=0;
  unsigned char last=c-FIRSTCHAR;

  for(i=0;i<SIZE;++i){
    used[i]=0;
  }
  
  for(i=0;i<SIZE;++i){
    tab[i]+=last;
    if(tab[i]>LASTCHAR){
      tab[i]-=SIZE;
    }
    while(used[tab[i]-FIRSTCHAR]){
      tab[i]++;
      if(tab[i]>LASTCHAR){
	tab[i]-=SIZE;
      }else if(tab[i]<FIRSTCHAR){
	tab[i]+=SIZE;
      }
    }

    used[tab[i]-FIRSTCHAR]=1;
    last=tab[i]-FIRSTCHAR;
  }
}

int find(unsigned char *tab,char c){
  int id=-1;

  if((c>=FIRSTCHAR && c<=LASTCHAR) || c=='\n'){
    id=0;
    while(id<SIZE && tab[id]!=c){
      ++id;
    }
  }

  return id;
}
/* ------------------------------------------------------ */

/* ------------------------------------------------------
 * Utilitaires
 */
void reverse(char * texte){
  int size = -1;
  int i;
  char c;

  while(texte[++size]);

  for(i=0;i<size/2;++i){
    c=texte[size-i-1];
    texte[size-i-1]=texte[i];
    texte[i]=c;
  }
}
/* ------------------------------------------------------ */
