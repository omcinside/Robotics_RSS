#include "Whisker.h"
#include <stdio.h>

int main()
{

  int x = 1;
  Whisker w;

  w.in(x, 3000);

  printf(" %d \n", w.state());

  return 0;

}
