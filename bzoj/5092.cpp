#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 3e6 + 10;

int n, f[N], a[N];

int main() {
    memset(f, 0x7f, sizeof f), f[0] = 0;
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]), a[i] ^= a[i - 1], f[a[i]] = min(f[a[i]], i);
    for(int j = 0 ; j <= 20 ; ++ j) {
        for(int i = 1 ; i <= int(2e6) ; ++ i) {
            if(!((i >> j) & 1)) {
                f[i] = min(f[i], f[i | (1 << j)]);
            }
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        int t = 0;
        for(int k = 20 ; ~ k ; -- k) {
            if(!((a[i] >> k) & 1) && f[t | (1 << k)] <= i) t |= 1 << k;
        }
        printf("%d\n", t + (t ^ a[i]));
    }
}

