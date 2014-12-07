/*function file uppgift 4*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.141592653589

/*Function that will be integrated*/
double getEnergy(double *x, double alfa)
{
  double energy;
  double r1Length = sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);
  double r2Length = sqrt(x[3]*x[3]+x[4]*x[4]+x[5]*x[5]);
  double r12 = sqrt((x[0]-x[3])*(x[0]-x[3])+(x[1]-x[4])*(x[1]-x[4])+(x[2]-x[5])*(x[2]-x[5]));
  double xNorm[6];
  double numerator=0;
  double denom=(1+alfa*r12)*(1+alfa*r12);
  int i;
  for( i=0; i<3;i++)
  {
    xNorm[i]=x[i]/r1Length;
    xNorm[i+3]=x[i+3]/r2Length;
  }
  for( i=0; i<3;i++)
  {
    numerator+= (xNorm[i]-xNorm[i+3])*(x[i]-x[i+3]); 
  }
  energy = -4.0+numerator/(r12*denom)-1.0/(r12*(1+alfa*r12)*denom)-1.0/(4.0*denom* denom)+1.0/r12;
  return energy;
}

/* Probability function*/
double rho(double *x, double alfa)
{
  double r1Length = sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);
  double r2Length = sqrt(x[3]*x[3]+x[4]*x[4]+x[5]*x[5]);
  double r12 = sqrt((x[0]-x[3])*(x[0]-x[3])+(x[1]-x[4])*(x[1]-x[4])+(x[2]-x[5])*(x[2]-x[5]));
  //normalization not needed due to only relative probabilities are considered
  double wFunc = exp(-2.0*r1Length)*exp(-2.0*r2Length)*exp(r12/(2.0*(1.0+alfa*r12)));

  return wFunc*wFunc;
}


/* Function that uses the Metropolis algorithm to
 * calculate the energy for the electronic ground state
 * of helium, by varying alpha to get the best approximation
 * for the wave function. */
void calcEChangeAlfa(double *returnValues, double alfa, double beta)
{
  /*declaration of variables*/
  int nRuns = 10000000; 
  int eqStep = 500; // length of equilibration
  double random_value;
  double var,errorBar;
  double s = 11.0; // value of s, calculated in problem 3
  double d = 1.0; //controlling acceptance 
  double x[6];
  double xTry[6];
  double term1,term2; //for calculating new alpha
  double q,energyTmp;
  double r12;
  double radie[2];
  double thrownValues; //for checking d-value
  double totalEnergy;
  double sqMean; //for calculating <f(x)^2>
  int n,i,j;

  /* Save function values in file */
  FILE *file;
  file = fopen("alfas.data","w");

  /* Random */
  srand(time(NULL));

  

  /* reset values that use += */
  thrownValues=0; //for checking d-value
  totalEnergy = 0.0;
  sqMean = 0.0; //for calculating <f(x)^2>
  term1 = 0.0;
  term2 = 0.0;


  /* Initialize the position of the electrons to -10 to 10 Bohr radii */
  for( i=0; i<6;i++)
  {
    x[i] = (((double) rand() / (double) RAND_MAX) - 0.5)*20.0;
  }

  /* Add a random displacement, -0.5 to 0.5 Bohr radii, to the coordinates of the electrons in every run and try if the change is accepted */
  for(n=0; n<nRuns;n++)
  {
    for( i=0; i<6;i++)
    {
      random_value=(double) rand() / (double) RAND_MAX;
      xTry[i] = x[i] + d*(random_value -0.5);
    }
    q=rho(xTry,alfa)/rho(x,alfa);
    if(q>=1)
    {
      for( i=0; i<6;i++)
      {
        x[i] = xTry[i];
      }
    }else
    {
      random_value=(double) rand() / (double) RAND_MAX;
      if(q>=random_value)
      {
        for( i=0; i<6;i++)
        {
          x[i] = xTry[i];
        }
      }else
      {
        ++thrownValues;
      }
    }

    /* After the initial equilibration is over the value for alpha is varied and the energy calculated. */
    if(n> eqStep)
    { 
      energyTmp=getEnergy(x,alfa);
      sqMean += energyTmp*energyTmp;
      totalEnergy+=energyTmp;

      /* Changing the value of alpha. */
      r12 = sqrt((x[0]-x[3])*(x[0]-x[3])+(x[1]-x[4])*(x[1]-x[4])+(x[2]-x[5])*(x[2]-x[5]));
      term1 += energyTmp * (-r12*r12 / (2.0* (1.0 + alfa * r12)*(1.0 + alfa * r12)));
      term2 += (-r12*r12 / (2.0* (1.0 + alfa * r12)*(1.0 + alfa * r12)));
      alfa += - (pow(n, -beta)* 2.0 * (term1 / (double) (n -eqStep) - totalEnergy / (double) (n -eqStep) * term2 / (double) (n- eqStep)));

  /* Print to file. */      
  fprintf(file,"%e\n",alfa);
     
    }
  }

  /* Checking percentage of thrown values. */
  printf("Thrown values: %.0f%%\n",100*thrownValues/(double)(nRuns));

  totalEnergy = totalEnergy / (double) (nRuns - eqStep);

  /* Calculating the variance/error bars. */
  sqMean = sqMean/(double) (nRuns - eqStep);
  var = sqMean-totalEnergy*totalEnergy;
  errorBar= s * (var/(double) (nRuns - eqStep));//calculating errorbars from variance

  /* Returns the calculated energy of the system and the variance. */
  returnValues[0]=totalEnergy;
  returnValues[1]=errorBar;  

  /* Close printing file. */
  fclose(file);
}
