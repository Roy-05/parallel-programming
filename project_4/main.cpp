#include <xmmintrin.h>
#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define SSE_WIDTH		4

#ifndef	SIZE
#define	SIZE			1024
#endif

#ifndef	NUMTRIES
#define	NUMTRIES		1000000
#endif

float A[SIZE];
float B[SIZE];

float SimdMulSum(float *, float *, int);
float NonSimdMulSum(float *, float *, int);

int main(int argc, char *argv[]) 
{
    
#ifndef _OPENMP
	fprintf( stderr, "No OpenMP support!\n" );
	return 1;
#endif

	double maxMegaMultsSimd = 0.;
	double maxMegaMultsNonSimd = 0.;
	// inialize the arrays:
	for( int i = 0; i < SIZE; i++ )
	{
		A[ i ] = 1.;
		B[ i ] = 2.;
	}

        for( int t = 0; t < NUMTRIES; t++ )
        {
                double time0 = omp_get_wtime( );
		SimdMulSum(A, B, SIZE);
 		double time1 = omp_get_wtime( );
                double megaMults = (double)SIZE/(time1-time0)/1000000.;
                if( megaMults > maxMegaMultsSimd )
                        maxMegaMultsSimd = megaMults;
	}

   	printf( "Peak Performance with SIMD    = %8.2lf MegaMults/Sec\n", maxMegaMultsSimd );

	for( int t = 0; t < NUMTRIES; t++ )
	{
	        double time0 = omp_get_wtime( );
		NonSimdMulSum(A, B, SIZE);
 		double time1 = omp_get_wtime( );
	        double megaMults = (double)SIZE/(time1-time0)/1000000.;
	        if( megaMults > maxMegaMultsNonSimd )
	                maxMegaMultsNonSimd = megaMults;
	}

   	printf( "Peak Performance without SIMD = %8.2lf MegaMults/Sec\n", maxMegaMultsNonSimd );
	printf("SpeedUp = %8.2lf\n", maxMegaMultsSimd/maxMegaMultsNonSimd);
}


float
SimdMulSum( float *a, float *b, int len )
{
	float sum[4] = { 0., 0., 0., 0. };
	int limit = ( len/SSE_WIDTH ) * SSE_WIDTH;
	register float *pa = a;
	register float *pb = b;

	__m128 ss = _mm_loadu_ps( &sum[0] );
	for( int i = 0; i < limit; i += SSE_WIDTH )
	{
		ss = _mm_add_ps( ss, _mm_mul_ps( _mm_loadu_ps( pa ), _mm_loadu_ps( pb ) ) );
		pa += SSE_WIDTH;
		pb += SSE_WIDTH;
	}
	_mm_storeu_ps( &sum[0], ss );

	for( int i = limit; i < len; i++ )
	{
		sum[0] += a[i] * b[i];
	}

	return sum[0] + sum[1] + sum[2] + sum[3];
}

float
NonSimdMulSum( float *a, float *b, int len)
{
	float sum = 0.;
	for(int i =0; i< len; i++)
	{
		sum += a[i] * b[i];
	}
	
	return sum;
}

