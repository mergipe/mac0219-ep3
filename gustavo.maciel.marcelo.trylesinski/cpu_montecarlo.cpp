#include "cpu_montecarlo.h"

#include <cmath>
#include <cstdlib>
#include <ctime>

//
static double f(int M, int k, double x)
{
    return sin((2 * M + 1) * M_PI * x) * cos(2 * M_PI * k * x) / sin(M_PI * x);
}

void sequential_montecarlo(uint64_t N, int k, int M, double *e_sum,
                           double *e_sub)
{
    double r_algb, r_sum, r_sub, f_val, f_avg, f_quad_avg, sqrt_val, x;

    if (fabs(k) <= fabs(M) && M >= 0)
        r_algb = 1;
    else if (fabs(k) <= fabs(M) && M < 0)
        r_algb = -1;
    else
        r_algb = 0;

    srand(time(NULL));
    f_avg = f_quad_avg = 0;

    for (uint64_t i = 0; i < N; i++)
    {
        x = ((double) rand() / RAND_MAX) * 0.5;
        f_val = f(M, k, x);
        f_avg += f_val;
        f_quad_avg += f_val * f_val;
    }

    f_avg /= N;
    f_quad_avg /= N;
    sqrt_val = sqrt((f_quad_avg - (f_avg * f_avg)) / N);
    r_sum = f_avg + sqrt_val;
    r_sub = f_avg - sqrt_val;
    *e_sum = fabs(r_algb - r_sum);
    *e_sub = fabs(r_algb - r_sub);
}
