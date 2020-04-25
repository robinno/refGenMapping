#include "..\Perf_counter.h"

void PCreset(perf_counter* c) {
	c->tot = c->cnt = c->calls = 0;
}

void PCstart(perf_counter* c) {
	c->cnt = sds_clock_counter();
	c->calls++;
}

void PCstop(perf_counter* c) {
	c->tot += (sds_clock_counter() - c->cnt);
}

uint64_t avg_cpu_cycles(perf_counter c) {
	return ((c.tot + (c.calls >> 1)) / c.calls);
}

