#include <bits/stdc++.h>
#define int long long
using namespace std;
 
const int T = 1e6, N = T + 10;
 
int n, a, b, c, d, k, mu[N], vis[N], prime[N], p;
 
void build() {
    mu[1] = 1;
    for(int i = 2 ; i <= T ; ++ i) {
        if(!vis[i]) prime[++ p] = i, mu[i] = -1;
        for(int j = 1 ; j <= p ; ++ j) {
            if(i * prime[j] > T) break;
            vis[i * prime[j]] = 1;
            if(i % prime[j]) mu[i * prime[j]] = -mu[i];
            else break;
        }
    }
    for(int i = 1 ; i <= T ; ++ i) mu[i] += mu[i - 1];
}
 
int sol(int a, int b) {
    if(!a || !b) return 0;
    int n = a / k, m = b / k, ans = 0;
    if(n > m) swap(n, m);
    for(int i = 1, j ; i <= n ; i = j + 1) {
        j = min(n / (n / i), m / (m / i));
        ans += (mu[j] - mu[i - 1]) * (n / i) * (m / j);
    }
    return ans;
}

signed main() {
    build();
    scanf("%lld%lld%lld", &b, &d, &k);
    printf("%lld\n", sol(b, d));
}

