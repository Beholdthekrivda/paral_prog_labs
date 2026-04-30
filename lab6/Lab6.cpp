#include <iostream>
#include <cmath>
#include <time.h>
#include "mpi.h"

using namespace std;

double f(double x, double y)
{
    return pow(x, 4) - pow(y, 4);
}

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand(time(NULL) + rank);

    double a = sqrt((1 + sqrt(5))/2), b = sqrt(1 + sqrt(5)), 
    c = sqrt(sqrt(2) - 1), d = 2 * sqrt(2/(1 + sqrt(17))), sum_local = 0;
    int N = pow(10, 7), N_local = N / size, N_in_local = 0;

    MPI_Barrier(MPI_COMM_WORLD);
    double start_time = MPI_Wtime();

    for (int i = 0; i < N_local; i++)
    {
        double x = a + rand()/(RAND_MAX+1.0)*(b-a);
        double y = c + rand()/(RAND_MAX+1.0)*(d-c);
        if ((x * y > 1 && x * y < 2) && (x*x - y*y > 1 && x*x - y*y < 2) && (x > 0))
        {
            N_in_local++; sum_local += f(x, y);
        }
    }
    
    double result_sum = 0;
    int N_in = 0;
    MPI_Reduce(&sum_local, &result_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&N_in_local, &N_in, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    result_sum *= ((b - a) * (d - c)) / N;

    double end_time = MPI_Wtime();
    double elapsed_time = end_time - start_time;

    if (rank == 0) 
    {
        cout << "Ответ = " << result_sum << endl;
        cout << "N_in = " << N_in << endl;
        cout << "Затраченное время = " << elapsed_time << endl; 
    }

    MPI_Finalize();
    return 0;
}