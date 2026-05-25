#include <iostream>
#include "mpi.h"
#include <time.h>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
    srand(time(NULL));

    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = (size + 1) * size / 2;
    vector<int> x_global(n);

    if (rank == 0)
    {
        for (int i = 0; i < n; i++)
        {
            x_global[i] = rand() % 19 - 9;
        }

        cout << "Массив x_global" << endl;
        for (int i = 0; i < n; i++)
        {
            printf("%d ", x_global[i]);
        }
        cout << endl;

        int ibeg = 0;
        for (int i = 0; i < size - 1; i++)
        {
            MPI_Send(&x_global[ibeg], i + 1, MPI_INT, i + 1, 0, MPI_COMM_WORLD);
            ibeg += i + 1;
        }

        printf("Процесс %d ничего не получил\n", rank);
    }
    else
    {
        vector<int> mass(rank);
        MPI_Recv(mass.data(), rank, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Процесс %d получил ", rank);
        for (int i = 0; i < rank; i++) printf("%d ", mass[i]);
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
