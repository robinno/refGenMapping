#include <stdint.h>
#include "stdlib.h"

typedef struct perf_counter perf_counter;

struct perf_counter{
     uint64_t tot, cnt, calls;
};

void PCreset(perf_counter* c);
void PCstart(perf_counter* c);
void PCstop(perf_counter* c);
uint64_t avg_cpu_cycles(perf_counter c);



