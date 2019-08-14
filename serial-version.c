#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SEED time(NULL)

double pi_serial_version(const int interval) {
  
  srand(SEED);

  double x, y;
  int i, points = 0;
  
  for (i = 0; i < interval; i ++) {
    x = rand() / (double) RAND_MAX;
    y = rand() / (double) RAND_MAX;
    
    if (x * x + y * y <= 1.0) points ++;
  }

  return (double) points / interval * 4.0;
}

int main(void) {

  clock_t start, end;

  start = clock();
  printf("\u03C0 \u2248 %f\n", pi_serial_version(1e9));
  end = clock();
  printf("Serial version time: %.5f\n", (double)(end - start) / CLOCKS_PER_SEC);

  return 0;
}
