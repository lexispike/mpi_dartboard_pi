/*
 * Alyxandra Spikerman
 * High Perfomance Computing
 * Homework 4 - Question 1
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, num_processors;

    MPI_Init(&argc, &argv); // being parallel code
    MPI_Comm_size(MPI_COMM_WORLD, &num_processors);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int chunk = 1000000000 / num_processors; // get the chunk value for each process to compute
    int total_hits = 0;
    int circle_hits = 0;
    float x, y, local_pi, pi_approximation;

    // assume a 2x2 square and a circle with radius 1
    // therefore x^2 + y^2 = 1 is the equation that makes the circle
    // if x^2 + y^2 <= 1, the dart hits the circle
    // then, 4 * # circle hits / total hits = pi
    srand(rank + 10);
    while (total_hits < chunk) {
        x = rand() / (float)RAND_MAX;
        y = rand() / (float)RAND_MAX;
        // printf("x: %f, y: %f\n", x, y);
        if ((x*x + y*y) <= 1.0) {
            circle_hits++;
        }
        total_hits++;
    }
    local_pi = 4 * circle_hits / (float)total_hits; // find the local approximation of pi
    printf("local_pi for %d rank with total_hits %d: %f\n", rank, total_hits, local_pi);

    // using MPI_Reduce, sum up all the local values of pi into rank 0's pi_approximation
    MPI_Reduce(&local_pi, &pi_approximation, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        pi_approximation = pi_approximation / num_processors; // get avg pi_approximation
        printf("Approximation of pi: %f\n", pi_approximation);
    }
    MPI_Finalize(); // end parallel code

    return 0;
}
