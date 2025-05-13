#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

double f(double x)
{
    return 2.755 * x * x - 3.7743 * x + 1.2311;
}

// Рекурсивный метод дихотомии
double f1(double l, double r, double pre)
{
    double m = (r - l) / 2.0 + l;

    if (std::abs(f(r) - f(l)) <= pre)
    {
        return m;
    }

    if (f(m - pre) < f(m + pre))
    {
        return f1(l, m, pre);
    }
    else
    {
        return f1(m, r, pre);
    }
}

// Итеративный метод дихотомии
double f2(double l, double r, double pre)
{
    double m = (r - l) / 2.0 + l;

    while (std::abs(f(r) - f(l)) > pre)
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

// Метод золотого сечения
double f3(double l, double r, double pre)
{
    const double phi = (1 + std::sqrt(5)) / 2.0; // Число золотого сечения
    double x1 = r - (r - l) / phi;
    double x2 = l + (r - l) / phi;

    while (std::abs(r - l) > pre)
    {
        if (f(x1) < f(x2))
        {
            r = x2;
            x2 = x1;
            x1 = r - (r - l) / phi;
        }
        else
        {
            l = x1;
            x1 = x2;
            x2 = l + (r - l) / phi;
        }
    }

    return (l + r) / 2.0;
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    char c = ' ';

    while (c != 'q')
    {
        int r = 0;
        double eps, rg;
        std::cout << "Precision as power of 10:" << std::endl;
        std::cin >> rg;
        eps = std::pow(10.0, -1.0 * rg);
        std::cout << "Iterations:" << std::endl;
        std::cin >> r;

        double time_f1_sum = 0, time_f2_sum = 0, time_golden_sum = 0;
        const double a = 0, b = 4;

        for (int k = 0; k < r; k++)
        {
            clock_t start = clock();
            f1(a, b, eps);
            clock_t end = clock();
            double seconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;
            time_f1_sum += seconds;

            start = clock();
            f2(a, b, eps);
            end = clock();
            seconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;
            time_f2_sum += seconds;

            start = clock();
            f3(a, b, eps);
            end = clock();
            seconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;
            time_golden_sum += seconds;
        }

        double time_1 = time_f1_sum / static_cast<double>(r);
        double time_2 = time_f2_sum / static_cast<double>(r);
        double time_3 = time_golden_sum / static_cast<double>(r);

        std::cout << "The time (recursion): " << time_1 << " seconds" << std::endl;
        std::cout << "The time (iteration): " << time_2 << " seconds" << std::endl;
        std::cout << "The time (golden section): " << time_3 << " seconds" << std::endl;

        std::cout << "Enter any char to continue; enter 'q' to exit." << std::endl;
        std::cin >> c;
    }

    return 0;
}

