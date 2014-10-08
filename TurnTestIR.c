#include <phidget21.h>
#include <pthread.h>
#include <stdio.h>
#include "Moto.h"

int main(int argc, char* argv[])
{
  Moto moto;
  moto.turnLeft(2400);
  moto.turnRight(2400);
  return 0;
};
