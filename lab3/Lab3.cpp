#include <iostream>
#include "mpi.h"
#include <time.h>

using namespace std;

int main(int argc, char** argv)
{
    srand(time(NULL));

    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int m = 4, n = m * size;
    int local_x[m], local_y[m], local_z[m], global_z[n];
    int *x = nullptr, *y = nullptr;

    if (size == 0)
    {
        printf("Некорректное число процессов\n");
        MPI_Finalize();
        return 0;
    }

    if (rank == 0)
    {
        x = new int[n]; y = new int[n];

        for (int i = 0; i < n; i++)
        {
            x[i] = rand() % 19 - 9;
            y[i] = rand() % 19 - 9;
        }

        printf("Исходные массивы\n");
        for (int i = 0; i < n; i++)
        {
            printf("%d ", x[i]);
        }
        printf("\n");
        for (int i = 0; i < n; i++)
        {
            printf("%d ", y[i]);
        }
    }

    MPI_Scatter(x, m, MPI_INT, local_x, m, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(y, m, MPI_INT, local_y, m, MPI_INT, 0, MPI_COMM_WORLD);

    // вычисление суммы
    for (int i = 0; i < m; i++)
    {
        local_z[i] = local_x[i] + local_y[i];
    }
    
    MPI_Allgather(local_z, m, MPI_INT, global_z, m, MPI_INT, MPI_COMM_WORLD);

    printf("\n");
    printf("Process %d. Result vector (size %d): ", rank, n);
    for (int i = 0; i < n; i++) 
    {
        printf("%d ", global_z[i]);
    }
    printf("\n");

    if (rank == 0)
    {
        delete[] x; delete[] y;
    }

    MPI_Finalize();
    return 0;
}