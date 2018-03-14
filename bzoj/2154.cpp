%:pragma GCC optimize(2)
%:pragma GCC optimize(3)

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e7 + 10;

const int mod = 20101009;

int n, m, pri[N], p, mu[N];

bool vis[N];

ll sum[N];

ll s(int x) { return (ll) x * (x + 1) / 2 % mod; }

ll ask(int a, int b) {
    ll res = 0;
    for(int i = 1, j ; i <= a && i <= b ; i = j + 1) {
        j = min(a / (a / i), b / (b / i));
        res = (res + (sum[j] - sum[i - 1] + mod) % mod * s(a / i) % mod * s(b / i) % mod) % mod;
    }
    return res;
}

const int M = 1e7;

int main() {
    mu[1] = sum[1] = 1;
    for(int i = 2 ; i <= M ; ++ i) {
        if(!vis[i]) pri[++ p] = i, mu[i] = -1;
        for(int j = 1 ; j <= p && pri[j] * i <= M ; ++ j) {
            vis[pri[j] * i] = 1;
            if(i % pri[j]) mu[pri[j] * i] = -mu[i];
            else break;
        }
        sum[i] = (sum[i - 1] + (ll) mu[i] * i * i + mod) % mod;
    }

    scanf("%d%d", &n, &m);
    ll ans = 0;
    for(int i = 1, j ; i <= n && i <= m ; i = j + 1) {
        j = min(n / (n / i), m / (m / i));
        ans = (ans + (s(j) - s(i - 1) + mod) % mod * ask(n / i, m / i)) % mod;
    }
    printf("%lld\n", ans);
}
