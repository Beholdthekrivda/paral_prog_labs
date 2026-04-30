#include <iostream>
#include "mpi.h"
#include <vector>
#include <cmath>

using namespace std;

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = 1000002;
    int *x = nullptr, *y = nullptr, local_x[n / size], local_y[n / size];

    if (rank == 0)
    {
        x = new int[n]; y = new int[n];

        for (int i = 0; i < n; i++)
        {
            x[i] = 1; y[i] = 1;
        }
    }

    MPI_Scatter(x, n / size, MPI_INT, local_x, n / size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(y, n / size, MPI_INT, local_y, n / size, MPI_INT, 0, MPI_COMM_WORLD);

    // скалярное произведение
    int s = 0;
    for (int i = 0; i < n / size; i++)
    {
        s += local_x[i] * local_y[i];
    }

    // алгоритм сдваивания
    int recv_val;
    for (int stage = 1, step = 1; step < size; stage++, step *= 2) 
    {
        if (rank % (2 * step) == 0) 
        {
            // Процесс-приёмник
            if (rank + step < size) 
            {
                MPI_Recv(&recv_val, 1, MPI_INT, rank + step, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                s += recv_val;
                printf("Процесс %d принял %d от процесса %d. Этап %d\n", rank, recv_val, rank + step, stage);
            }
        } 
        else if (rank % (2 * step) == step) 
        {
            // Процесс-отправитель
            MPI_Send(&s, 1, MPI_INT, rank - step, 0, MPI_COMM_WORLD);
            printf("Процесс %d отправил %d процессу %d. Этап %d\n", rank, s, rank - step, stage);
        }
    }

    // Вывод результата на процессе 0
    if (rank == 0) 
    {
        printf("Итоговая сумма = %d\n", s);
        printf("Ожидаемая сумма = %d\n", n);
    }

    MPI_Finalize();
    return 0;
}