#ifndef CPU_MONTECARLO_H_
#define CPU_MONTECARLO_H_

#include <cstdint>

//
void sequential_montecarlo(uint64_t N, int k, int M, double *e_sum,
                           double *e_sub);

#endif
