/*Home Problem 2b uppgift 1,2,3 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "calcEKeepAlfa.h"

#define PI 3.141592653589
// TODO plot spread of alpha - nRuns, and spread alpha constant startposition
int main()
{

    double alfa = 0.05; // lowest alpha to check
    double alfaMax = 0.25; // highest alpha to check
    double alfaAdd = 0.005;// How much to increment alpha every while loop
    int nSameAlpha = 10;// How many times to run for same alpha
    double energy[2]; //for storing energy and error bar from one run
    int j;
    FILE *file;
    file = fopen("../savedData/alfaCompare.data","w");
    //loop different alpha
    /*-------------------uppgift 3-------------------*/ 
    while (alfa <= alfaMax)
    {
        energy[0]=0;
        energy[1]=0;
        /*run same alpha several times */
        for(j=0; j<nSameAlpha ; j++)
        {
            /*add calculated energy with error bar to energy
             * for calculated alpha */
            calcEKeepAlfa(energy, alfa);
            // print here to see how much calculation varies for same alpha
            //fprintf(file,"%f\t%e\t%e\n", alfa, energy[0]/ (double) (j + 1.0), energy[1]/ (double) (j + 1.0));
        }

        /*calculate mean value for several same alpha values before print */
        energy[0] = energy[0] / (double) (nSameAlpha );
        energy[1] = energy[1] / (double) (nSameAlpha * 2.0);//times two to get +/- value, not total errorbar length
        fprintf(file,"%f\t%e\t%e\n", alfa, energy[0], energy[1]);
        /*increment alpha for next run */
        alfa += alfaAdd;
    }

    fclose(file);
    return 0;
}
