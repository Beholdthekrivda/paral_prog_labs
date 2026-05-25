#include <iostream>
#include <cmath>
#include <omp.h>

using namespace std;

double f(double x)
{
    return asin(x/0.2)/x;
}

int main()
{
    double a = 0.1, b = 0.16;
    int n = pow(10, 8);
    double h = (b - a) / n, sum = 0;

    double endpoints = (f(a) + f(b)) / 2;

    int p[9] = {1, 2, 4, 8, 12, 16, 20, 24, 32};

    for (int i = 0; i < 9; i++)
    {
        omp_set_num_threads(p[i]);

        double start = omp_get_wtime();

        #pragma omp parallel for reduction(+:sum)
        for (int i = 0; i < n; i++)
        {
            double x = a + i * h;

            sum += f(x);
        }

        double end = omp_get_wtime();

        sum = (sum + endpoints) * h;

        cout << "Кол-во нитей: " << omp_get_max_threads() << endl;
        cout << "Результат: " << sum << endl;
        cout << "Время: " << end - start << endl;
        cout << endl;

        sum = 0;
    }
    
    return 0;
}