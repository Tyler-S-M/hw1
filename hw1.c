/* hw1.c
 *
 * Simple vector-matrix multiply code.
 *
 */

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include "cblas.h"

#define N 1024		// length of vector, length and width of matrix
#define SEED 1		// random number seed
#define REPS 1000	// repetitions
//#define OUT   	// output flag

double vector[N];
double matrix[N][N];
double result[N];

void initialize();
void vm_multiply_parallel();
void vm_multiply_sequential();
void output();

void reset_vect(){
	for (int i = 0; i < N; i ++)
		result[i] = 0.0;
}

double timeSub(struct timespec end, struct timespec start){

	double returnVal = 0.0;
		
	returnVal += ((double)(end.tv_nsec - start.tv_nsec))/1000000000;
	returnVal += (end.tv_sec - start.tv_sec);

	return returnVal;

}

int main() {
	int i;
	struct timespec start;
	struct timespec end;

	initialize();

    	clock_gettime(CLOCK_MONOTONIC, &start);
	for (i=0; i<REPS; i++) {
		vm_multiply_parallel();
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	printf("Time Taken OpenMP: %lf\n", timeSub(end, start));

	output();

	double aggregate = 0.0;
	for (i=0; i<REPS; i++) {
		clock_gettime(CLOCK_MONOTONIC, &start);
		cblas_dgemv(CblasRowMajor, CblasNoTrans, N, N, 1.0, (const double*)matrix, N, vector, 1, 1.0, result, 1);
		clock_gettime(CLOCK_MONOTONIC, &end);
		aggregate += (timeSub(end, start));

		if (i != REPS-1)
			reset_vect();
	}
	printf("Time Taken CBlas: %lf\n", aggregate);

	output();

	clock_gettime(CLOCK_MONOTONIC, &start);
	for (i=0; i<REPS; i++) {
		vm_multiply_sequential();
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	printf("Time Taken Sequential: %lf\n", timeSub(end, start));

	output();
	return 0;
}

void initialize() {
	int i,j;

	srand(SEED);
	for (i=0; i<N; i++) {
		vector[i] = (double)rand()/RAND_MAX;
		result[i] = 0.0;
		for (j=0; j<N; j++) {
			matrix[i][j] = (double)rand()/RAND_MAX;
		}
	}
}


void vm_multiply_parallel() {
	int i,j;

	#pragma omp parallel
	{	
		#pragma omp for
		for (j=0; j<N; j++) {
			result[j] = 0.0;
			for (i=0; i<N; i++) {
				result[j] += vector[i]*matrix[j][i];
			}
		}
	}
}

void vm_multiply_sequential() {
	int i,j;

	for (j=0; j<N; j++) {
		result[j] = 0.0;
		for (i=0; i<N; i++) {
			result[j] += vector[i]*matrix[j][i];
		}
	}
}

void output() {
#ifdef OUT
	printf("result:");
	for (int i=0; i<N; i++) {
		if (i%10 == 0)
			printf("\n");
		printf(" %6.4f",result[i]);
	}
	printf("\n");
#else
	return;
#endif
}
