#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define SEED time(NULL)

int main(int argc, char **argv) {

  int rank, size;
  unsigned int seed;
  double x, y, start, end;
  long long int i, j, all_point, points, all_intern;

  FILE *fp = fopen("simulation-mpi.txt", "w");
  long long int dim[] = {5, 50, 500, 5000, 50000, 500000, 5000000, 50000000};

  MPI_Init(&argc, &argv);
  start = MPI_Wtime();

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  seed = SEED + rank;

  for ( j = 0; j < 8; j++ ) {
    points = 0;

    for ( i = 0; i < dim[j]; i++ ) {
      x = (double) rand_r(&seed) / RAND_MAX;
      y = (double) rand_r(&seed) / RAND_MAX;

      if ( x * x + y * y <= 1.0 ) points++;
    }

    MPI_Reduce(&points, &all_intern, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    all_point = dim[j] * size;

    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();

    if ( rank == 0 ) {
      printf("\u03C0 \u2248 %Lf\n", (long double) all_intern / all_point * 4.0);
      printf("Time elapsed: %.4f\n", end - start);
      fprintf(fp, "%lld\t%Lf\t%.4f\n", all_point, (long double) all_intern / all_point * 4.0, end - start);
    }
  }

  MPI_Finalize();
  fclose(fp);
  return 0;
}

// int main(int argc, char **argv) {
  
//   pi_mpi_version(argc, argv);
//   if ( argc == 2 )
//   else 
//     printf("Error, specify the number of sample to be generate");

//   return 0;
// }
