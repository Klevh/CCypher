#include "file.h"

void freeListChar(ListChar l){
  Element *e=l.first,*nxt;
  while(e!=NULL){
    nxt=e->nxt;
    free(e);
    e=e->nxt;
  }
}

char* ltoa(ListChar l){
  char *s=NULL;
  int i;
  Element *e;

  if(l.taille>-1 || (l.taille>0 && l.first)){
    s=malloc((l.taille+1)*sizeof(*s));
    e=l.first;
    i=0;
    while(i<l.taille && e){
      *(s+i)=e->c;
      e=e->nxt;
      ++i;
    }
    if(i<l.taille){
      free(s);
      s=NULL;
    }else{
      s[i]='\0';
    }
  }

  return s;
}

char* read_str(FILE *stream, int * n,char end){
  ListChar l;
  char c=EOF,*s=NULL;
  Element *e;

  if(stream){
    /*init de la liste*/
    l.taille=-1;
    l.first=NULL;

    /*lecture*/
    c=getc(stream);
    if(c!=end){
      l.taille=0;
      l.first=malloc(sizeof(*(l.first)));
      e=l.first;
      e->c=c;
      l.taille=1;
      c=getc(stream);
      while(c!=end){
	e->nxt=malloc(sizeof(*(e->nxt)));
	e=e->nxt;
	e->c=c;
	++(l.taille);
	c=getc(stream);
      }
      e->nxt=NULL;
    }else if(c!=end){
      l.taille=1;
      l.first=malloc(sizeof(*(l.first)));
      l.first->c=0;
      l.first->nxt=NULL;
    }

    /* enregistrement de la taille */
    if(n){
      *n=l.taille;
    }
    
    /*convertion en chaine de caractere*/
    s=ltoa(l);

    /*liberation de la liste*/
    freeListChar(l);
  }

  return s;
}
