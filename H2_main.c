/*Home Problem 4 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.141592653589
/*function that will be integrated*/
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
double rho(double *x, double alfa)
{
    double r1Length = sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);
    double r2Length = sqrt(x[3]*x[3]+x[4]*x[4]+x[5]*x[5]);
    double r12 = sqrt((x[0]-x[3])*(x[0]-x[3])+(x[1]-x[4])*(x[1]-x[4])+(x[2]-x[5])*(x[2]-x[5]));
    //normalization not needed due to only relative probabilities are considered
    double wFunc = exp(-2.0*r1Length)*exp(-2.0*r2Length)*exp(r12/(2.0*(1.0+alfa*r12)));

    return wFunc*wFunc;
}

int main ()
{
    /*declaration of variables*/
    int nRuns = 1000000;
    int eqStep = 500;
    double random_value;
    double totalEnergy = 0.0;
    double var,errorBar;
    double alfa=0.1;
    double d = 1.0;//controlling acceptance 
    double sqMean = 0.0;//for calculating <f(x)^2>
    double x[6];
    double xTry[6];
    double q,energyTmp;
    double radie[2];
    /*Save function values in file*/
    FILE *file;
    FILE *genPoints;
    file = fopen("energy.data","w");
    genPoints = fopen("genPoints.data","w");
    srand(time(NULL));
    int n,i;
    double thrownValues=0;//for checking deltavalue
    for( i=0; i<6;i++)
    {
        x[i] = (((double) rand() / (double) RAND_MAX) - 0.5)*2.0;
    }
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
        if(n> eqStep)
        { //throw away some values
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
            fprintf(genPoints,"%e\n%e\n",sqrt(radie[0]),sqrt(radie[1]));
            fprintf(file,"%e\t%e\n",energyTmp, totalEnergy/(double)(n+1-eqStep));
        }
    }

    printf("Thrown values: %.0f%%\n",100*thrownValues/(double)(nRuns));
    totalEnergy = totalEnergy / (double) (nRuns - eqStep);
    sqMean = sqMean/(double)nRuns;
    var = sqMean-totalEnergy*totalEnergy;
    errorBar=sqrt(var/(double)nRuns);//calculating errorbars from variance
    printf("Value of integral: %f\nlength of errorbar:  %f\n",totalEnergy,errorBar);

    fclose(file);
    fclose(genPoints);
    return 0;
}
