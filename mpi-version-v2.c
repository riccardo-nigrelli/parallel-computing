#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>

#define SEED time(NULL)

int main(int argc, char **argv) {

  double x, y, start, end;
  int i, size, rank;
  unsigned int seed;
  long long int all_point, interval = 1000000, points = 0;
  long long int sum = 0, *receiver = NULL;

  MPI_Init(&argc, &argv);
  start = MPI_Wtime();

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  seed = SEED + rank;
  // long long int receiver[size];
  receiver = malloc(size * sizeof(long long int));
  if ( receiver == NULL ) {
    perror("Unable to allocate memory");
    abort();
  }

  if ( rank != 0 ) {
    for ( i = 0; i < interval; i++ ) {
      x = (double) rand_r(&seed) / RAND_MAX;
      y = (double) rand_r(&seed) / RAND_MAX;

      if ( x * x + y * y <= 1.0 ) points++;
    }

    for ( i = 0; i < size; i++ ) 
      MPI_Send(&points, 1, MPI_LONG_DOUBLE_INT, 0, 1, MPI_COMM_WORLD);
  }

  all_point = interval * size;

  if ( rank == 0 ) {    
    for ( i = 0; i < size; i++ ) 
      MPI_Recv((receiver + i), size, MPI_LONG_LONG_INT, MPI_ANY_SOURCE, 1,\
        MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
    for ( i = 0; i < size; i++ ) sum += receiver[i];
    end = MPI_Wtime();

    printf("\u03C0 \u2248 %Lf\n", (long double) sum / all_point * 4.0);
    printf("Time elapsed: %.4f\n", end - start);
  }

  MPI_Finalize();

  return 0;
}
