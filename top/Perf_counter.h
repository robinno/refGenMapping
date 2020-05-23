#include "stdlib.h"

//the performance counter
typedef struct perf_counter perf_counter;
struct perf_counter{
     unsigned long long tot, cnt, calls;
};

//resets the performance counter
void PCreset(perf_counter* c);

//starts the counter
void PCstart(perf_counter* c);

//stops the counter
void PCstop(perf_counter* c);

//returns the average time between start and stop of the performance counter
unsigned long long avg_cpu_cycles(perf_counter c);



