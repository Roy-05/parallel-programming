#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <omp.h>

unsigned int seed = 0;  // To seed the random number generator

// Function Prototypes

float   Ranf(unsigned int *, float, float);
int     Ranf(unsigned int *, int, int);
float   SQR(float);
void    Grain();
void    GrainDeer();
void    Watcher();

// State of the environment

int NowYear;		// 2020 - 2025
int	NowMonth;		// 0 - 11

float	NowHeight;		// grain height in inches
int	    NowNumDeer;		// number of deer in the current population
float   NowPrecip;		// inches of rain per month
float	NowTemp;		// temperature this month

const float GRAIN_GROWS_PER_MONTH =		9.0;    // in inches
const float ONE_DEER_EATS_PER_MONTH =   1.0;

const float AVG_PRECIP_PER_MONTH =		7.0;	// average, in inches
const float AMP_PRECIP_PER_MONTH =		6.0;	// plus or minus
const float RANDOM_PRECIP =			    2.0;	// plus or minus noise

const float AVG_TEMP =				60.0;	// average, in Fahrenheit
const float AMP_TEMP =				20.0;	// plus or minus
const float RANDOM_TEMP =			10.0;	// plus or minus noise

const float MIDTEMP =				40.0;
const float MIDPRECIP =				10.0;

float x = Ranf( &seed, -1.f, 1.f );

int main(int argc, char *argv[]) 
{
    
#ifndef _OPENMP
	fprintf( stderr, "No OpenMP support!\n" );
	return 1;
#endif

    // Set Up initial Environmental Parameters
    NowMonth    =   0;
    NowYear     =   2020;
    NowNumDeer  =   1;
    NowHeight   =   1.;

    float ang = (  30.*(float)NowMonth + 15.  ) * ( M_PI / 180. );

    float temp = AVG_TEMP - AMP_TEMP * cos( ang );
    NowTemp = temp + Ranf( &seed, -RANDOM_TEMP, RANDOM_TEMP );

    float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
    NowPrecip = precip + Ranf( &seed,  -RANDOM_PRECIP, RANDOM_PRECIP );
    
    if( NowPrecip < 0. ){
        NowPrecip = 0.;
    }

    // Spawn threads for functional decomposition
    omp_set_num_threads(3);
    #pragma omp parallel sections
    {
        #pragma omp section 
        {
            GrainDeer();
        }

        #pragma omp section 
        {
            Grain();
        }

        #pragma omp section 
        {
            Watcher();
        }

        // #pragma omp section {
        //     MyAgent();
        // }
    }  

    printf("\nCurrent Date: %d/%d\n", NowMonth+1, NowYear);
    printf("Simulation Complete!\n");
}

void GrainDeer() {
    while(NowYear < 2026)
    {   
        float nextNumDeer = NowNumDeer;
        if(nextNumDeer <= floor(NowHeight)){
            nextNumDeer++;
        }
        else{
            nextNumDeer--;
        }

        // DoneComputing barrier:
        #pragma omp barrier

        NowNumDeer = nextNumDeer;

        // DoneAssigning barrier:
        #pragma omp barrier

        // DonePrinting barrier:
	    #pragma omp barrier
    }
}

void Grain() {
    while(NowYear < 2026)
    {   
        // Compute condition for grain growth
        float tempFactor = exp(   -SQR(  ( NowTemp - MIDTEMP ) / 10.  )   );
        float precipFactor = exp(   -SQR(  ( NowPrecip - MIDPRECIP ) / 10.  )   );

        float nextHeight = NowHeight;
        nextHeight += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
        nextHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;
        
        if(nextHeight < 0.0){
            nextHeight = 0.0;
        }

        // DoneComputing barrier:
        #pragma omp barrier

        NowHeight = nextHeight;

        // DoneAssigning barrier:
        #pragma omp barrier

        // DonePrinting barrier:
	    #pragma omp barrier
    }
}

// Watcher Thread to maintain global state
void 
Watcher()
{      
    while(NowYear < 2026)
    {
        // DoneComputing barrier:
        #pragma omp barrier

        // DoneAssigning barrier:
        #pragma omp barrier

        // // Print current state of environment:
        // printf("Current Date          : %d/%d\n", NowMonth+1, NowYear);
        // printf("Current Grain Height  : %2.3f cm\n", NowHeight*2.54);
        // printf("Current Number of Deer: %d\n", NowNumDeer);
        // printf("Current Precipitation : %2.3f cm\n", NowPrecip*2.54);
        // printf("Current Temperature   : %2.3f C\n\n", (5.0/9.0)*(NowTemp-32));

        // Print data for graph:
        printf("%2.4f\t%d\t%2.4f\t%2.4f\n", NowHeight*2.54, NowNumDeer, NowPrecip*2.54,  (5.0/9.0)*(NowTemp-32));

        // Calculate and Update environment variables
        if(NowMonth <11){
            NowMonth++;
        }
        else {
            NowMonth = 0;
            NowYear++;
        }

        float ang = (  30.*(float)NowMonth + 15.  ) * ( M_PI / 180. );

        float temp = AVG_TEMP - AMP_TEMP * cos( ang );
        NowTemp = temp + Ranf( &seed, -RANDOM_TEMP, RANDOM_TEMP );

        float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
        NowPrecip = precip + Ranf( &seed,  -RANDOM_PRECIP, RANDOM_PRECIP );
        
        if( NowPrecip < 0. ){
            NowPrecip = 0.;
        }

        // DonePrinting barrier:
	    #pragma omp barrier
    }
}


// Helper Functions:

float
SQR( float x )
{
        return x*x;
}


float
Ranf( unsigned int *seedp,  float low, float high )
{
        float r = (float) rand_r( seedp );              // 0 - RAND_MAX

        return(   low  +  r * ( high - low ) / (float)RAND_MAX   );
}


int
Ranf( unsigned int *seedp, int ilow, int ihigh )
{
        float low = (float)ilow;
        float high = (float)ihigh + 0.9999f;

        return (int)(  Ranf(seedp, low,high) );
}

