#include <iostream>
#include <vector>
#include <time.h>

double f(double x)
{
    return 2.755 * x * x - 3.7743 * x + 1.2311;
}

double f2(double l, double r, double pre) 
{
    double m = (r - l) / 2.0 + l;

    while (abs(f(r) - f(l)) > pre) 
    {
        if (f(m - pre) < f(m + pre)) 
        {
            r = m;
        }
        else 
        {
            l = m;
        }

        m = (r - l) / 2.0 + l;
    }

    return m;
}

double f1(double l, double r, double pre) 
{
    double m = (r - l) / 2.0 + l;

    if (abs(f(r) - f(l)) <= pre) 
    {
        return m;
    }

    if (f(m - pre) < f(m + pre)) 
    {
        m = f1(l, m, pre);
    }
    else 
    {
        m = f1(m, r, pre);
    }

    return m;
}

int main() 
{
    srand(static_cast<unsigned int>(time(NULL)));
    char c = ' ';

    while (c != 'q')
    {   
        int r = 0;
        double eps, rg;
        std::cout << "Precision as power of 10:" << std::endl;
        std::cin >> rg;
        eps = pow(10.0, -1 * rg);
        std::cout << "Iterations:" << std::endl;
        std::cin >> r;

        double time_f1_sum = 0, time_f2_sum = 0;
        const double a = 0, b = 4;

        for (int k = 0; k < r; k++)
        {
            clock_t start = clock();
            f1(a, b, eps);
            clock_t end = clock();
            double seconds = (double)(end - start) / CLOCKS_PER_SEC;
            time_f1_sum += seconds;

            start = clock();
            f2(a, b, eps);
            end = clock();
            seconds = (double)(end - start) / CLOCKS_PER_SEC;
            time_f2_sum += seconds;
        }
        
        double time_1 = time_f1_sum / (double)r;
        std::cout << "The time (recursion): " << time_1 << " seconds" << std::endl;
        double time_2 = time_f2_sum / (double)r;
        std::cout << "The time (iteration): " << time_2 << " seconds" << std::endl;

        std::cout << "Enter any char to continue; enter 'q' to exit." << std::endl;
        std::cin >> c;
    }

    return 0;
}
