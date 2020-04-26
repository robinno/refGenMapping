#include "stdlib.h"

typedef struct perf_counter perf_counter;

struct perf_counter{
     unsigned long long tot, cnt, calls;
};

void PCreset(perf_counter* c);
void PCstart(perf_counter* c);
void PCstop(perf_counter* c);
unsigned long long avg_cpu_cycles(perf_counter c);



