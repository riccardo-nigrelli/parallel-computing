#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define SEED time(NULL)

void pi_mpi_version(int argc, char **argv) {

  int rank, size;
  unsigned int seed;
  double x, y, start, end;
  long long int i, all_point, points = 0, all_intern;

  MPI_Init(&argc, &argv);
  start = MPI_Wtime();

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  seed = SEED + rank;

  for ( i = 0; i < atoll(argv[1]); i++ ) {
    x = (double) rand_r(&seed) / RAND_MAX;
    y = (double) rand_r(&seed) / RAND_MAX;

    if ( x * x + y * y <= 1.0 ) points++;
  }

  MPI_Reduce(&points, &all_intern, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  all_point = atoll(argv[1]) * size;

  MPI_Barrier(MPI_COMM_WORLD);
  end = MPI_Wtime();

  if ( rank == 0 ) {
    printf("\u03C0 \u2248 %Lf\n", (long double) all_intern / all_point * 4.0);
    printf("Time elapsed: %.4f\n", end - start);
  }

  MPI_Finalize();
}

int main(int argc, char **argv) {

  pi_mpi_version(argc, argv);

  return 0;
}
