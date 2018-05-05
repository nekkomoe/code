#include <bits/stdc++.h>

using namespace std;

const int N = 2e6 + 10;

int n, m;

struct P {
    int x, y, c;
} p[N];

bool operator < (P a, P b) {
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}

int pos[N], f[N];

int calc(P a, P b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d%d%d", &p[i].x, &p[i].y, &p[i].c);
    }
    sort(p + (pos[1] = 1), p + 1 + n);
    for(int i = 1 ; i <= n ; ++ i) {
        int mx = 0xcfcfcfcf;
        for(int j = 1 ; j <= p[i].y ; ++ j) {
            if(pos[j]) {
                mx = max(mx, f[j] - calc(p[i], (P) { pos[j], j, 0 }));
            }
        }
        pos[p[i].y] = p[i].x, f[p[i].y] = mx + p[i].c;
    }
    printf("%d\n", f[m]);
}
