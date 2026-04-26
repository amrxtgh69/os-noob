#include <stdlib.h>
void func() {
  int *x = (int *) malloc(sizeof(int));
  
  free(x);
}
