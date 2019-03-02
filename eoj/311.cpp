#include "test.h"

int Solve() {
    int N = 1e9 + 10;
    return Query(N - Query(N) - 1) + 1;
}
