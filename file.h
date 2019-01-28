#ifndef CRYPT_FILE_KLEVH
#define CRYPT_FILE_KLEVH

#include <stdio.h>
#include <stdlib.h>

/*liste de caractere*/
typedef struct Element{
  struct Element *nxt;
  char c;
}Element;
typedef struct{
  Element *first;
  int taille;
}ListChar;

/*desalloue une liste de caractere*/
void freeListChar(ListChar);
/*transforme une liste de caractere en chaine de caractere si celle ci est bien construite, sinon NULL*/
char* ltoa(ListChar);
/*lit une chaine de caractere dans le fichier stream et la retourne, retoune NULL si cela n'est pas possible. Ne ferme pas le fichier.*/
char* read_str(FILE *,int * n,char end);

#endif
