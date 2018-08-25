#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 2010;

int n;

struct P {
    ll x, y;
} p[N];

ll operator * (P a, P b) {
    return a.x * b.y - b.x * a.y;
}

P operator - (P a, P b) {
    return (P) { a.x - b.x, a.y - b.y };
}

ll ans;

struct T {
    P p;
    double val;
} t[N];

bool operator < (T a, T b) {
    return a.val < b.val;
}

ll calc(ll n) {
    return n * (n - 1) / 2;
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld%lld", &p[i].x, &p[i].y);
    }
    if(n < 6) {
        puts("0");
        return 0;
    }
    for(int i = 1 ; i <= n ; ++ i) {
        // printf("fafa in %d, (%lld, %lld): \n", i, p[i].x, p[i].y);
        int tot = 0;
        for(int j = 1 ; j <= n ; ++ j) {
            if(j != i) {
                t[tot].val = atan2(p[i].y - p[j].y, p[i].x - p[j].x);
                t[tot].p = (P) { p[j].x - p[i].x, p[j].y - p[i].y };
                ++ tot;
            }
        }
        sort(t, t + tot);
        // for(int j = 0 ; j < tot ; ++ j) {
        //     printf("(%lld, %lld)\n", t[j].p.x, t[j].p.y);
        // }
        for(int j = 0, k = 0 ; j < tot ; ++ j) {
            while(t[j].p * t[(k + 1) % tot].p > 0) k = (k + 1) % tot;
            ll s = 0;
            if(k - j >= 0) s = k - j;
            else s = tot - j + k;
            // printf("j = %d, k = %d\n", j, k);
            if(j == k) {
                // 摸了
            } else {
                ans += calc(s) * calc(tot - s - 1);
                // printf("+= %lld (s = %lld)\n", calc(s) * calc(tot - s - 1), s);
            }
        }
    }
    ans /= 2;
    printf("%lld\n", ans);
}
