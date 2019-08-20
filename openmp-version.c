#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define SEED time(NULL)

double pi_openmp_version(const int interval, const int thread, double *timer) {

  int i, points = 0;
  double x, y, start;
  
  start = omp_get_wtime();
  #pragma omp parallel num_threads(thread)  reduction(+:points)
  {

    srand(SEED);

    #pragma omp for
    for ( i = 0; i < interval; i++ ) {
      x = rand() / (double) RAND_MAX;
      y = rand() / (double) RAND_MAX;
      
      if (x * x + y * y <= 1.0) points ++;
    }
  }
  (*timer) = omp_get_wtime() - start;

  return (double) points / interval * 4.0;
}

int main(int argc, char **argv) {

  if ( argc == 3 ) {
    double time;

    printf("\u03C0 \u2248 %f\n", pi_openmp_version(atoi(argv[1]), atoi(argv[2]), &time));
    printf("OpenMP version time: %.5f\n", time);
  }
  else if ( argc <= 1 ) {
    printf("ERROR! Specify the number of iternation and the number of the thread to use\n");
    exit(1);
  }
  else exit(1);

  return 0;
}
