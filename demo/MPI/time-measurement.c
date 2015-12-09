#include <stdio.h>
#include <mpi.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int rank;
    double start_time;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0)
        start_time = MPI_Wtime();

    sleep(1);

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0)
        printf("Execution time: %lf\n", MPI_Wtime() - start_time);

    MPI_Finalize();
    return 0;
}
