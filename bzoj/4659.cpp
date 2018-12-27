#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int T = 4e6, N = T + 10, mod = 1 << 30;

int n, m, mu[N], pri[N], tot, vis[N], f[N], g[N], k[N];

inline int S(int n, int m) {
    return (((ll) (1 + n) * n) >> 1) * (((ll) (1 + m) * m) >> 1);
}

int main() {
    mu[1] = f[1] = 1;
    for(int i = 2 ; i <= T ; ++ i) {
        if(!vis[i]) {
            mu[i] = -1;
            f[i] = i * (1 - i);
            g[i] = i;
            k[i] = 1;
            pri[++ tot] = i;
        }
        for(int j = 1 ; j <= tot && i * pri[j] <= T ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) {
                g[i * pri[j]] = g[i] * pri[j];
                k[i * pri[j]] = k[i] + 1;
                f[i * pri[j]] = -f[i / g[i]] * g[i * pri[j]] * pri[j] * (k[i] + 1 == 2);
                break;
            } 
            mu[i * pri[j]] = -mu[i];
            f[i * pri[j]] = f[i] * f[pri[j]];
            g[i * pri[j]] = pri[j];
            k[i * pri[j]] = 1;
        } 
    }
    
    for(int i = 1 ; i <= T ; ++ i)
        f[i] += f[i - 1];
    
    int t; scanf("%d", &t); 
    while(t --) {
        scanf("%d%d", &n, &m); 
        if(n > m) swap(n, m);
        int ans = 0;
        for(int i = 1, j ; i <= n ; i = j + 1) {
            j = min(n / (n / i), m / (m / i));
            ans += (f[j] - f[i - 1]) * S(n / i, m / i);
        } 
        printf("%d\n", (ans & ((1 << 30) - 1)));
    } 
}

