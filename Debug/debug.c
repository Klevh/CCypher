#include <stdlib.h>

int main(){
  system("rm ../Files/r");
  system("rm ../Files/rr");
  system("../nothing 0 ../Files/t ../Files/r");
  system("../nothing 1 ../Files/r ../Files/rr");

  return 0;
}
