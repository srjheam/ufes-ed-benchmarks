#include "profiler.h"

double get_timestamp() { return clock() / (double)CLOCKS_PER_SEC; }

double mmin(double a, double b) { return a < b ? a : b; }

double mmax(double a, double b) { return a > b ? a : b; }
