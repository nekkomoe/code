#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

typedef long long ll;

const int N = 2e6 + 10;

int n;

ll a[N], f[N];

struct P {
    ll x, y;
} q[N];

P operator - (P a, P b) {
    return (P) { a.x - b.x, a.y - b.y };
}

ll operator * (P a, P b) {
    return a.x * b.y - b.x * a.y;
}

ll calc(P p, int i) {
    return (p.y + 2ll * a[i] + (ll) i * i - i - 2ll * i * p.x) / 2;
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%lld", &a[i]);
    for(int i = 1, l = 1, r = 1 ; i <= n ; ++ i) {
        while(l < r && calc(q[l], i) > calc(q[l + 1], i)) ++ l;

        f[i] = calc(q[l], i);

        P p = (P) { i, 2ll * f[i] + (ll) i * i + i };

        while(l < r && (q[r] - q[r - 1]) * (p - q[r - 1]) < 0) -- r;

        q[++ r] = p;

    }
    printf("%lld\n", f[n]);
}


