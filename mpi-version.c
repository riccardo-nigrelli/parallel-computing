#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>

#define SEED time(NULL)

double pi_mpi_version(int argc, char **argv) {

  int i, rank, size, total_iteration, total_points = 0, points = 0;
  double x, y, start, end, total_time;

  MPI_Init( &argc, &argv );
  start = MPI_Wtime();

  srand(SEED);
  
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  
  for ( i = 0; i < atoi(argv[1]); i++ ) {
    x = rand() / (double) RAND_MAX;
    y = rand() / (double) RAND_MAX;

    if ( x * x + y * y <= 1.0 ) points++;
  }

  total_iteration = size * atoi(argv[1]);

  MPI_Barrier(MPI_COMM_WORLD);
  
  MPI_Reduce(&points, &total_points, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  
  end = MPI_Wtime() - start;
  MPI_Reduce(&end, &total_time, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  if ( rank == 0 ) {
    printf("\u03C0 \u2248 %f\n", (double) total_points / total_iteration * 4.0);
    printf("Total time: %f\n", total_time);
  }

  MPI_Finalize();
  return .6;

}

int main(int argc, char **argv) {

  pi_mpi_version(argc, argv);

  return 0;
}
