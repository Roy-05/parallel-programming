#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

// setting the number of threads:
#ifndef NUMT
#define NUMT		1
#endif

// setting the number of trials in the monte carlo simulation:
#ifndef NUMTRIALS
#define NUMTRIALS	1000000
#endif

// how many tries to discover the maximum performance:
#ifndef NUMTRIES
#define NUMTRIES	10
#endif

// ranges for the random numbers:
const double XCMIN =	-1.0;
const double XCMAX =	 1.0;
const double YCMIN =	 0.0;
const double YCMAX =	 2.0;
const double RMIN  =	 0.5;
const double RMAX  =	 2.0;

// function prototypes:
double		Ranf( double, double );
int			Ranf( int, int );
void		TimeOfDaySeed( );

// main program:
int main( int argc, char *argv[ ] )
{
#ifndef _OPENMP
	fprintf( stderr, "No OpenMP support!\n" );
	return 1;
#endif

	double tn = tan( (M_PI/180.)*30. );
	TimeOfDaySeed( );		// seed the random number generator

	omp_set_num_threads( NUMT );	// set the number of threads to use in the for-loop:`
	
	// better to define these here so that the rand() calls don't get into the thread timing:
	double *xcs = new double [NUMTRIALS];
	double *ycs = new double [NUMTRIALS];
	double * rs = new double [NUMTRIALS];
	
	// fill the random-value arrays:
	for( int n = 0; n < NUMTRIALS; n++ )
	{       
			xcs[n] = Ranf( XCMIN, XCMAX );
			ycs[n] = Ranf( YCMIN, YCMAX );
			rs[n] = Ranf(  RMIN,  RMAX ); 
	}       

	// get ready to record the maximum performance and the probability:
	double maxPerformance = 0.;      // must be declared outside the NUMTRIES loop
	double currentProb;              // must be declared outside the NUMTRIES loop

	// looking for the maximum performance:
	for( int t = 0; t < NUMTRIES; t++ )
	{
			double time0 = omp_get_wtime( );

			int numHits = 0;
		#pragma omp parallel for default(none) shared(xcs,ycs,rs,tn) reduction(+:numHits)
		for( int n = 0; n < NUMTRIALS; n++ )
		{
			// randomize the location and radius of the circle:
			double xc = xcs[n];
			double yc = ycs[n];
			double  r =  rs[n];

			// solve for the intersection using the quadratic formula:
			double a = 1. + tn*tn;
			double b = -2.*( xc + yc*tn );
			double c = xc*xc + yc*yc - r*r;
			double d = b*b - 4.*a*c;	

			if( d < 0 )
				continue;
			
			// hits the circle:
			// get the first intersection:
			d = sqrt( d );
			double t1 = (-b + d ) / ( 2.*a );	// time to intersect the circle
			double t2 = (-b - d ) / ( 2.*a );	// time to intersect the circle
			double tmin = t1 < t2 ? t1 : t2;		// only care about the first intersection

			if( tmin < 0 )
				continue;

			// where does it intersect the circle?
			double xcir = tmin;
			double ycir = tmin*tn;

			// get the unitized normal vector at the point of intersection:
			double nx = xcir - xc;
			double ny = ycir - yc;
			double n = sqrt( nx*nx + ny*ny );
			nx /= n;	// unit vector
			ny /= n;	// unit vector

			// get the unitized incoming vector:
			double inx = xcir - 0.;
			double iny = ycir - 0.;
			double in = sqrt( inx*inx + iny*iny );
			inx /= in;	// unit vector
			iny /= in;	// unit vector

			// get the outgoing (bounced) vector:
			double dot = inx*nx + iny*ny;
			double outx = inx - 2.*nx*dot;	// angle of reflection = angle of incidence`
			double outy = iny - 2.*ny*dot;	// angle of reflection = angle of incidence`

			// find out if it hits the infinite plate:
			double t = ( 0. - ycir ) / outy;

			if (t < 0 )
				continue;	
			else
				numHits += 1;

		}
		double time1 = omp_get_wtime( );
		double megaTrialsPerSecond = (double)NUMTRIALS / ( time1 - time0 ) / 1000000.;
		if( megaTrialsPerSecond > maxPerformance )
			maxPerformance = megaTrialsPerSecond;
		currentProb = (double)numHits/(double)NUMTRIALS;
	}
	
	printf("%lf",maxPerformance);
}
	

double Ranf( double low, double high )
{
        double r = (double) rand();               // 0 - RAND_MAX
        double t = r  /  (double) RAND_MAX;       // 0. - 1.

        return   low  +  t * ( high - low );
}

int Ranf( int ilow, int ihigh )
{
        double low = (double)ilow;
        double high = ceil( (double)ihigh );

        return (int) Ranf(low,high);
}

void TimeOfDaySeed( )
{
	struct tm y2k = { 0 };
	y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

	time_t  timer;
	time( &timer );
	double seconds = difftime( timer, mktime(&y2k) );
	unsigned int seed = (unsigned int)( 1000.*seconds );    // milliseconds
	srand( seed );
}
