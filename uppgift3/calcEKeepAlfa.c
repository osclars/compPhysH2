/*function file*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.141592653589
/*function that calculates local energy */
double getEnergy(double *x, double alfa)
{
    double energy;
    /* distance from nucleus and from each other */
    double r1Length = sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);
    double r2Length = sqrt(x[3]*x[3]+x[4]*x[4]+x[5]*x[5]);
    double r12 = sqrt((x[0]-x[3])*(x[0]-x[3])+(x[1]-x[4])*(x[1]-x[4])+(x[2]-x[5])*(x[2]-x[5]));
    /* normalized positions */
    double xNorm[6];

    /* For saving space in energy expression */
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

/* function that uses the Metropolis algorithm to
 * calculate the energy for the ground state
 * of helium, alpha is a parameter in the approximated 
 * wave function*/
void calcEKeepAlfa(double *returnValues, double alfa)
{
    /*declaration of variables*/
    int nRuns = 1000000; //number of actual calculations are nRuns - eqStep
    int eqStep = 500; //no calculations are made intill after 500 steps
    double random_value; // for storing latest calculated random value
    double s = 11.0;// statistical inefficiency  
    double d = 1.0;//controlling acceptance rate (thrownValues) 
    double x[6]; // for storing positions
    double xTry[6]; // new configuration that might get accepted
    double q,energyTmp; // q is how likely the new config is to get accepted 
    double radie[2]; // checking how the distance to the nucleus varies during simulation
    /*Save values in file, used in problem 1 and 2*/
    //FILE *file;
    //FILE *genPoints;
    //file = fopen("allEnergy.data","w");
    //genPoints = fopen("genPoints.data","w");
    srand(time(NULL));
    int n,i,j;
    double thrownValues;//for checking value of d, should be 50%
    double totalEnergy;
    double var,errorBar,sqMean;//for calculating error bars


    /* reset values that use += */
    thrownValues=0;//for checking deltavalue
    totalEnergy = 0.0;
    sqMean = 0.0;//for calculating <f(x)^2>

    /* initial positions are randomized, -10 - 10*/ 
    for( i=0; i<6;i++)
    {
        x[i] = (((double) rand() / (double) RAND_MAX) - 0.5)*20.0;
    }
    /* start main algorithm */
    for(n=0; n<nRuns;n++)
    {
        /* new configuration (based on old one) is created */
        for( i=0; i<6;i++)
        {
            random_value=(double) rand() / (double) RAND_MAX;
            xTry[i] = x[i] + d*(random_value -0.5);
        }
        /* calculate how likely the new config is to be accepted */  
        q=rho(xTry,alfa)/rho(x,alfa);
        /* no need to calculate a new random value if q > 1 */ 
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
        /* Only calculate properties after equilibration */  
        if(n> eqStep)
        { 
            energyTmp=getEnergy(x,alfa);
            sqMean += energyTmp*energyTmp;
            totalEnergy+=energyTmp;
            radie[0]=0;
            radie[1]=0;
            for( i=0; i<3;i++)
            {
                radie[0]+=x[i]*x[i];
                radie[1]+=x[i+3]*x[i+3]; 
            }
            /* used in problem 1 and 2 (with eqStep set to 0) */
            //fprintf(genPoints,"%e\n%e\n",sqrt(radie[0]),sqrt(radie[1]));
            //fprintf(file,"%e\t%e\n",energyTmp, totalEnergy/(double)(n+1-eqStep));
        }
    }

    // print thrown values percent to check d- value 
    //printf("Thrown values: %.0f%%\n",100*thrownValues/(double)(nRuns));

    /* caclulate mean of properties for all runs */
    totalEnergy = totalEnergy / (double) (nRuns - eqStep);
    sqMean = sqMean/(double) (nRuns - eqStep);
    var = sqMean-totalEnergy*totalEnergy;
    errorBar= s * (var/(double) (nRuns - eqStep));//calculating errorbars from variance

    /* add values to */
    returnValues[0]+=totalEnergy;
    returnValues[1]+=errorBar;  
    //fclose(file);
    //fclose(genPoints);
}
