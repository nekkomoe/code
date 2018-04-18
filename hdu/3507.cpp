#include <bits/stdc++.h>

using namespace std;

const int N = 500000 + 10;

int n, c[N], m, l, r;

typedef long long ll;

ll s[N], f[N];

struct P { ll x, y; } q[N];

P operator - (P a, P b) { return (P) { a.x - b.x, a.y - b.y }; }

ll operator * (P a, P b) { return a.x * b.y - b.x * a.y; }

ll calc(int i, P p) { return p.y + s[i] * s[i] + m - 2 * s[i] * p.x; }

int main() {
    while(scanf("%d%d", &n, &m) == 2) {
        l = r = 1;
        for(int i = 1 ; i <= n ; ++ i) {
            scanf("%d", &c[i]), s[i] = s[i - 1] + c[i];
        }
        for(int i = 1 ; i <= n ; ++ i) {
            while(l < r && calc(i, q[l]) >= calc(i, q[l + 1])) l ++;
            f[i] = calc(i, q[l]);
            P p = (P) { s[i], f[i] + s[i] * s[i] };
            while(l < r && (p - q[r - 1]) * (q[r] - q[r - 1]) >= 0) r --;
            q[++ r] = p;
        }
        printf("%lld\n", f[n]);
    }
}
