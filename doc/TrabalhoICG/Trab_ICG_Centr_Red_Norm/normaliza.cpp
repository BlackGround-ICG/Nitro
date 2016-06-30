#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mesh.h"
#include <list>
#include <iostream>
#include <math.h>

using namespace std;

void normalizaVetor(float a, float b, float c){
  float norma = 0;
  norma = sqrt(pow(a,2) + pow(b,2) + pow(c,2));
  printf("A: %.5f B: %.5f C:%.5f\n",a,b,c);
  printf("Norma: %.5f\n", norma);
  a = a/norma*1.0;
  c = b/norma*1.0;
  c = c/norma*1.0;
  printf("Normalizados: %.5f %.5f %.5f\n",a,b,c);
}
int main(){


	normalizaVetor(0.678884, -0.218787, 0.700827);
}