#include "..\Perf_counter.h"

void PCreset(perf_counter* c) {
	c->tot = 0;
	c->cnt = 0;
	c->calls = 0;
}

void PCstart(perf_counter* c) {
	c->cnt = sds_clock_counter();
	c->calls++;
}

void PCstop(perf_counter* c) {
	c->tot += (sds_clock_counter() - c->cnt);
}

unsigned long long avg_cpu_cycles(perf_counter c) {
	return (c.tot / c.calls);
}

