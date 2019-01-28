#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "crypt.h"

#define CHAR_SIZE 201

int main(int argc, char *argv[])
{
  char *key, *keyTab;
  
  if(argc==4 && strcmp(argv[2],argv[3])){
    if(argv[1][0] && !argv[1][1] && (argv[1][0]=='0' || argv[1][0]=='1')){
      system("reset");
      key=read_str(stdin,NULL,'\n');
      if(key){
	system("reset");
	keyTab=read_str(stdin,NULL,'\n');
	system("reset");
	if(keyTab){
	  if(argv[1][0]=='0'){
	    cypher(key,keyTab,argv[2],argv[3]);
	  }else{
	    decypher(key,keyTab,argv[2],argv[3]);
	  }
	}
      }
    }
  }
  
  return 0;
}
