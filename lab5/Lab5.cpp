#include <iostream>
#include <cmath>
#include "mpi.h"

using namespace std;

double f(double x)
{
    return (1 - exp(0.7/x)) / (2 + x);
}

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double a = 1, b = 3;
    int n = 10000000, local_n = n / size;
    double h = (b - a) / n, local_sum = 0;

    MPI_Barrier(MPI_COMM_WORLD);
    double start_time = MPI_Wtime();

    for (int i = 1; i <= local_n; i++)
    {
        int left_idx = (i - 1) + rank * local_n;
        int right_idx = i + rank * local_n;

        double x_left = a + left_idx * h;
        double x_right = a + right_idx * h;

        double mid = 0.5 * (x_left + x_right);
        local_sum += f(mid);
    }

    local_sum = local_sum * h;

    double global_sum = 0;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();
    double elapsed_time = end_time - start_time;

    if (rank == 0) 
    {
        cout << "Ответ = " << global_sum << endl;
        cout << "Затраченное время = " << elapsed_time << endl;
    }

    MPI_Finalize();
    return 0;
}