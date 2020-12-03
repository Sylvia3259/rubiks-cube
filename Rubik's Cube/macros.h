#pragma once
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define ABS(x) ((x) < 0 ? -(x) : (x))
#define SWAP(t, a, b) { t temp = (a); (a) = (b); (b) = temp; }