#define _XOPEN_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define SEED time(NULL)

double pi_openmp_version(const long long int interval, const int thread, double *timer) {
  
  unsigned int seed;
  int i, points = 0;
  double x, y, start;  

  start = omp_get_wtime();
  #pragma omp parallel num_threads(thread) private(seed, x, y) reduction(+:points)
  {

    seed = SEED * omp_get_thread_num();

    #pragma omp for
    for ( i = 0; i < interval; i++ ) {
      x = (double) rand_r(&seed) / RAND_MAX;
      y = (double) rand_r(&seed) / RAND_MAX;
      
      if (x * x + y * y <= 1.0) points ++;
    }
  }
  (*timer) = omp_get_wtime() - start;

  return (double) points / interval * 4.0;
}

int main(void) { // int argc, char **argv

  int i;
  double pi, time;
  long long int dim[] = {100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

  FILE *fp = fopen("simulation-omp.txt", "w");
  
  for ( i = 0; i < 8; i++ ) {
    // clock_t end, start = clock();
    pi = pi_openmp_version(dim[i], 20, &time);
    // end = clock() - start;
    fprintf(fp, "%lld\t%.4f\t%.5f\n", dim[i], pi, time);
  }
    
  fclose(fp);

  // if ( argc == 3 ) {
  //   double time;

  //   printf("\u03C0 \u2248 %f\n", pi_openmp_version(atoi(argv[1]), atoi(argv[2]), &time));
  //   printf("OpenMP version time: %.5f\n", time);
  // }
  // else if ( argc <= 1 ) {
  //   printf("ERROR! Specify the number of iternation and the number of the thread to use\n");
  //   exit(1);
  // }
  // else exit(1);

  return 0;
}