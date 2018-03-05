#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int n, a;

int main() {
    while(scanf("%d", &n) == 1) {
        a = 0;
        for(int i = n ; i ; -- i) scanf("%d", &n), a ^= n;
        puts(a ? "Yes" : "No");
    }
}
