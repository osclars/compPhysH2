/*Home Problem 2b uppgift 3 och 4 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "calcEChangeAlfa.h"

#define PI 3.141592653589

int main()
{

  double alfa = 0.06; // (0.05,0.25)
  double beta = 0.6; //[0.6,1.0]
  double energy[2]; // for storing energy and error bar from one run

  FILE *file;
  file = fopen("../savedData/alfaChange.data","w");

  /* Changing alpha and calculating the energy. */ 
  calcEChangeAlfa(energy, alfa, beta); 

  /* Printing what is returned for above function to file. */
  fprintf(file,"%f\t%e\t%e\n", alfa, energy[0], energy[1]); // used for problem 4
  //  printf("Energy:%e\t Errorbar:%e\n",energy[0], energy[1]); // used for problem 5
  fclose(file);
  return 0;
}
