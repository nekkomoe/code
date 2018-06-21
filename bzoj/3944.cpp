#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e6;
ll n, phi[N + 10], mu[N + 10], pri[N + 10], tot, p[N + 10], q[N + 10];

bool vis[(int) 1e5 + 10];

ll getp(ll x) { return x <= N ? phi[x] : p[n / x]; }
ll getq(ll x) { return x <= N ? mu[x] : q[n / x]; }

void sol(ll x) {
    if(x <= N || vis[n / x]) return ;
    vis[n / x] = 1;
    p[n / x] = (1 + x) * x / 2;
    q[n / x] = x >= 1;
    for(ll i = 2, j ; i <= x ; i = j + 1) {
        j = x / (x / i);
        sol(x / i);
        p[n / x] -= getp(x / i) * (j - i + 1);
        q[n / x] -= getq(x / i) * (j - i + 1);
    }
}

int main() {
    mu[1] = phi[1] = 1;
    for(int i = 2 ; i <= N ; ++ i) {
        if(!phi[i]) phi[i] = i - 1, mu[i] = -1, pri[++ tot] = i;
        for(int j = 1 ; j <= tot && i * pri[j] <= N ; ++ j) {
            if(i % pri[j] == 0) {
                phi[i * pri[j]] = phi[i] * pri[j];
                break;
            } else {
                phi[i * pri[j]] = phi[i] * (pri[j] - 1);
                mu[i * pri[j]] = -mu[i];
            }
        }
        mu[i] += mu[i - 1];
        phi[i] += phi[i - 1];
    }
    int T; scanf("%d", &T);
    while(T --) {
        scanf("%lld", &n);
        memset(vis, 0, sizeof vis);
        if(n <= N) printf("%lld %lld\n", phi[n], mu[n]);
        else sol(n), printf("%lld %lld\n", p[1], q[1]);
    }
}
