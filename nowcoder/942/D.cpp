#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e7 + 10;
typedef long double ld;
int n, L;
ll a[N], x, y, z, m;
ld ans;

struct P {
    ld x, y;
};
P operator - (P a, P b) {
    return (P) { a.x - b.x, a.y - b.y };
}
ld operator * (P a, P b) {
    return a.x * b.y - b.x * a.y;
}
P sta[N];
ld calc(P a, P b) {
    return (ld) (a.y - b.y) / (a.x - b.x);
}

int main() {
    scanf("%d%d", &n, &L);
    scanf("%lld%lld%lld%lld%lld", &a[1], &x, &y, &z, &m);

//    assert(L == 1); // 10%
//    assert(n <= 1000); // 20%
//    assert(n <= int(1e5)); // 40%
//    assert(m <= 10 && L <= int(1e5)); // ano 20%
    assert(m % 2 == 0 && 1 <= L && L <= n && n <= int(1e7) && 1 <= min(min(min(a[1], x), min(y, z)), m) && max(max(max(a[1], x), max(y, z)), m) <= int(1e9)); // 100%

    for(int i = 2 ; i <= n ; ++ i) {
        a[i] = ((x * a[i - 1] % m * a[i - 1] % m + y * a[i - 2] % m + z) % m + m) % m - m / 2;
    }
    for(int i = 2 ; i <= n ; ++ i) {
        a[i] += a[i - 1];
    }
    ans = (ld) a[n] / n;
    
    // (a[i] - a[j]) / (i - j)

    // (i, a[i])
    int ql = 1, qr = 1;
    for(int i = L ; i <= n ; ++ i) {
        P p; p.x = i, p.y = a[i];
        while(qr - ql + 1 >= 2 && i - sta[ql + 1].x >= L && calc(p, sta[ql]) <= calc(p, sta[ql + 1])) {
            ++ ql;
        }
        if(ql <= qr && i - sta[ql].x >= L) {
            ans = max(ans, calc(p, sta[ql]));
        }

        if(i - L + 1 >= 1) {
            p.x = i - L + 1, p.y = a[i - L + 1];
            while(qr - ql + 1 >= 2 && (sta[qr - 1] - sta[qr]) * (p - sta[qr]) >= 0) -- qr;
            sta[++ qr] = p;
        }
    }

    cout << fixed << setprecision(8) << ans << endl;
}
