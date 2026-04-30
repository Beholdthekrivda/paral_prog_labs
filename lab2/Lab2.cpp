#include <iostream>
#include <time.h>
#include "mpi.h"

using namespace std;

int main(int argc, char** argv)
{
    srand(time(NULL));

    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size <= 1)
    {
        printf("Процессов меньше 2\n");
        MPI_Finalize();
        return 0;
    }

    int n = 4 * size, m = 5, count = 0;
    int A_local[4][m]; int A_global[n][m];
    // заполняем массив значениями 
    if (rank == 0)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                A_global[i][j] = rand() % 19 - 9;
            }
        }

        printf("Матрица\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                printf("%d ", A_global[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    MPI_Scatter(A_global, 4 * m, MPI_INT, A_local, 4 * m, MPI_INT, 0, MPI_COMM_WORLD);
    
    printf("Процесс %d получил строки:\n", rank);
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < m; j++) printf("%d ", A_local[i][j]);
        printf("\n");
    }
    printf("\n");

    // локальный подсчет четных чисел
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < m; j++)
        {
            if (A_local[i][j] % 2 == 0) count++;
        }
    }

    // суммирование кол-ва четных чисел
    int total_count;
    MPI_Reduce(&count, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Кол-во четных чисел: %d\n", total_count);
    }

    MPI_Finalize();
    return 0;
}