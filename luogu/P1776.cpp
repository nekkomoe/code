#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 110, M = 4e4 + 10, Q = 1e6 + 10;

int f[N][M], n, m;
int que[Q], l, r, que_val[Q];

void add(int pos, int value, int weight, int count) {
    for(int b = 0 ; b <= min(m, weight - 1) ; ++ b) {
        l = 1, r = 0;
        for(int a = 0, t = 0 - count ; a * weight + b <= m ; ++ a) {
            // t in [a - count, a]
            int j = a * weight + b;
            while(l <= r && que[l] < a - count) ++ l;
            while(t <= a) {
                if(t * weight + b >= 0) {
                    int val = f[pos - 1][t * weight + b] - t * value;
                    while(l <= r && que_val[r] <= val) -- r;
                    ++ r;
                    que[r] = t;
                    que_val[r] = val;
                }
                ++ t;
            }
            if(l <= r) {
                f[pos][j] = max(f[pos][j], que_val[l] + a * value);
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        int v, w, c;
        scanf("%d%d%d", &v, &w, &c);
        add(i, v, w, c);
    }
    printf("%d\n", f[n][m]);
}
