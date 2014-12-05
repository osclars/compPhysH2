/*Home Problem 2b uppgift 3 och 4 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "calcEChangeAlfa.h"

#define PI 3.141592653589

int main()
{

  double alfa = 0.1; 
  double beta = 1.0;
  double energy[2]; //for storing energy and error bar from one run
  int i;
  //FILE *file;
  //file = fopen("../savedData/alfaChange.data","w");

  calcEChangeAlfa(energy, alfa, beta); 
  //fprintf(file,"%f\t%e\t%e\n", alfa, energy[0], energy[1]);

  //fclose(file);
  return 0;
}
