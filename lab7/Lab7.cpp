#include <iostream>
#include <time.h>
#include <omp.h>

using namespace std;

double ikj(int** A, int** B, int**& C, int n, int m, int K, int chunk = 1)
{
    double start = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic, chunk)
    for (int i = 0; i < m; i++)
    {
        for (int k = 0; k < K; k++)
        {
            for (int j = 0; j < n; j++) C[i][j] += A[i][k] * B[k][j];
        }
    }

    double end = omp_get_wtime();
    return end - start;
}

double kij(int** A, int** B, int**& C, int n, int m, int K, int chunk = 1)
{
    double start = omp_get_wtime();
 
    // при каждой итерации цикла for k будет создаваться и завершаться параллельная область
    // это даст накладные расходы, поэтому инициализация параллельной части вынесена перед циклом for k
    #pragma omp parallel 
    for (int k = 0; k < K; k++)
    {
        #pragma omp for schedule(dynamic, chunk)
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++) C[i][j] += A[i][k] * B[k][j];
        }
    }

    double end = omp_get_wtime();
    return end - start;
}

int main()
{
    srand(time(NULL));

    int n = 1024, m = 1024;
    int** A = new int*[n];
    int** B = new int*[m];
    int** C = new int*[n];
    int k = m;

    for (int i = 0; i < n; i++)
    {
        A[i] = new int[m];
        for (int j = 0; j < m; j++)
        {
            A[i][j] = 0 + rand() % 10;
        }
    }

    for (int i = 0; i < m; i++)
    {
        B[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            B[i][j] = 0 + rand() % 10;
        }
    }

    for (int i = 0; i < n; i++) C[i] = new int[n];

    int p[9] = {1, 2, 4, 8, 12, 16, 20, 24, 32};
    int chunks[5] = {1, 4, 16, 64, 256};

    for (int i = 0; i < 9; i++)
    {
        omp_set_num_threads(p[i]);

        cout << "Кол-во нитей: " << omp_get_max_threads() << endl;

        double min = ikj(A, B, C, n, n, m), chunk = 1;

        cout << "i-k-j" << endl;
        for (int c : chunks)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++) C[i][j] = 0;
            }

            double result = ikj(A, B, C, n, n, m, c);
            if (result < min)
            {
                min = result; chunk = c;
            }
        }

        cout << "Время: " << min << " Кол-во chunk: " << chunk << endl;

        min = kij(A, B, C, n, n, m), chunk = 1;

        cout << "k-i-j" << endl;
        for (int c : chunks)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++) C[i][j] = 0;
            }

            double result = kij(A, B, C, n, n, m, c);
            if (result < min)
            {
                min = result; chunk = c;
            }
        }

        cout << "Время: " << min << " Кол-во chunk: " << chunk << endl;
        cout << endl;
    }

	return 0;
}
