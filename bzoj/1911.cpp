#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e6 + 10;

struct P {
    ll x, y;
} q[N];

P operator - (P a, P b) {
    return (P) { a.x - b.x, a.y - b.y };
}

ll operator * (P a, P b) {
    return a.x * b.y - a.y * b.x;
}

int l, r, n;

ll a, b, c, x[N], s[N], f[N];

ll calc(int i, P p) {
    return a * s[i] * s[i] + b * s[i] + c + p.y - 2 * a * s[i] * p.x;
}

int main() {
    scanf("%d%lld%lld%lld", &n, &a, &b, &c);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &x[i]);
        s[i] = s[i - 1] + x[i];
    }
    for(int i = 1 ; i <= n ; ++ i) {
        while(l < r && calc(i, q[l]) <= calc(i, q[l + 1])) l ++;
        f[i] = calc(i, q[l]);
        P p = (P) { s[i], f[i] + a * s[i] * s[i] - b * s[i] };
        while(l < r && (q[r] - q[r - 1]) * (p - q[r - 1]) >= 0) r --;
        q[++ r] = p;
    }
    printf("%lld\n", f[n]);
}
