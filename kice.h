#ifndef SCRYPT_HEADER_KLEVH
#define SCRYPT_HEADER_KLEVH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

#define SIZE 96
#define FIRSTCHAR 31
#define LASTCHAR 126
#define DBG(i,j) printf("%d - %d\n",i,j)

/* ------------------------------------------------------
 * decypher
 */
/*decypher file using both keys*/
void decypher(char* key,char* keyTab,char * from, char * to);
/*apply the decypher with c*/
void applyDecypher(char * text,char ch,unsigned char* tab,int idLast);
/* ------------------------------------------------------ */



/* ------------------------------------------------------
 * cypher
 */
/*cypher text using both keys*/
void cypher(char* key, char* keyTab,char * from, char * to);
/*apply the cypher with c*/
void applyCypher(char * text,char c,unsigned char* tab);
/* ------------------------------------------------------ */



/* ------------------------------------------------------
 * tab
 */
/*generate the shuffled ascii tab acording to the key*/
unsigned char* generateTab(char* key);
/*apply one shuffle to tab using c*/
void shuffle(unsigned char *tab,char c);
/*find c in tab*/
int find(unsigned char *tab,char c);
/* ------------------------------------------------------ */

/* ------------------------------------------------------
 * Utilitaires
 */
void reverse(char * texte);
/* ------------------------------------------------------ */

#endif
