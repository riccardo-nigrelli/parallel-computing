#define _XOPEN_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SEED time(NULL)

double pi_serial_version(const long long int interval) {
  
  srand(SEED);

  double x, y;
  int i, points = 0;
  
  for (i = 0; i < interval; i ++) {
    x = (double) rand() / RAND_MAX;
    y = (double) rand() / RAND_MAX;
    
    if (x * x + y * y <= 1.0) points ++;
  }

  return (double) points / interval * 4.0;
}

int main(void) { //int argc, char **argv

  int i;
  double pi;
  long long int dim[] = {100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

  FILE *fp = fopen("simulation-serial.txt", "w");
  
  for ( i = 0; i < 8; i++ ) {
    clock_t end, start = clock();
    pi = pi_serial_version(dim[i]);
    end = clock() - start;
    fprintf(fp, "%lld\t%.4f\t%.5f\n", dim[i], pi, (double)(end) / CLOCKS_PER_SEC);
  }
    
  fclose(fp);

  // if ( argc == 2 ) {
  //   clock_t start = clock();
  //   printf("\u03C0 \u2248 %f\n", pi_serial_version(atoi(argv[1])));
  //   printf("Serial version time: %.5f\n", (double)(clock() - start) / CLOCKS_PER_SEC);
  // }
  // else if ( argc <= 1 ) {
  //   printf("ERROR! Specify the number of thread to use\n");
  //   exit(1);
  // }
  // else exit(1);

  return 0;
}
