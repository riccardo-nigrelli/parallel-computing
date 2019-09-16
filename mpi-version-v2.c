#define _XOPEN_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>

#define SEED time(NULL)

int main(int argc, char **argv) {
  
  int rank, size;
  unsigned int seed;
  double x, y, start, end;
  long long int i, all_point, points = 0;
  long long int sum = 0;

  MPI_Init(&argc, &argv);
  start = MPI_Wtime();

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  seed = SEED + rank;
  
  long long int receiver[size];
  
  if ( rank != 0 ) {
    for ( i = 0; i < atoll(argv[1]); i++ ) {
      x = (double) rand_r(&seed) / RAND_MAX;
      y = (double) rand_r(&seed) / RAND_MAX;

      if ( x * x + y * y <= 1.0 ) points++;
    }

    for ( i = 0; i < size; i++ )
      MPI_Send(&points, 1, MPI_LONG_DOUBLE_INT, 0, 1, MPI_COMM_WORLD);
  }

  all_point = atoll(argv[1]) * size;

  MPI_Barrier(MPI_COMM_WORLD);
  end = MPI_Wtime();

  if ( rank == 0 ) {
    for ( i = 0; i < size; i++ )
      MPI_Recv(&receiver[i], size, MPI_LONG_LONG_INT, MPI_ANY_SOURCE, 1,\
        MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
    for ( i = 0; i < size; i++ ) sum += receiver[i];  

    printf("\u03C0 \u2248 %Lf\n", (long double) sum / all_point * 4.0);
    printf("Time elapsed: %.4f\n", end - start);
  }

  MPI_Finalize();
  
  return 0;
}

// int main(int argc, char **argv) {

//   if ( argc == 2 )
//     pi_mpi_v2_version(argc, argv);
//   else if ( argc <= 1 ) {
//     printf("Error, specify the number of sample to be generate");
//     exit(1);
//   }

//   return 0;
// }
