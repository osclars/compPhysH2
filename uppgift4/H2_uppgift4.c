/*Home Problem 2b uppgift 4 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.141592653589

int main()
{

  double alfa = 0.05; //start at lowest alfa to check
  double alfaMax = 0.25;
  double alfaAdd = 0.005;// How much to increment alfa every while loop
  int nSameAlpha = 10;
  double energy[2]; //for storing energy and error bar from one run
  int i,j,n;
  FILE *file;
  file = fopen("../savedData/alfaCompare.data","w");
  //loop different alfa
  energy[0]=0;
  energy[1]=0;
  //run same alfa several times
  for(j=0; j<nSameAlpha ; j++)
  {
    /*add calculated energy with error bar to energy
     * for calculated alpha */
    calcEnergy(energy, alfa);
  }

  /*normalize before print */
  energy[0] == energy[0] / (double) nSameAlpha;
  energy[1] == energy[1] / (double) nSameAlpha;
  fprintf(file,"%f\t%e\t%e\n", alfa, energy[0], energy[1]);

  fclose(file);
  return 0;
}
