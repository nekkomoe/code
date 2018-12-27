#include <bits/stdc++.h>
 
using namespace std;
 
const int T = 1e5, N = T + 10;
 
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
//    for(int i = 1 ; i <= T ; ++ i) mu[i] += mu[i - 1];
}

int main() {
    scanf("%d", &n);
    build();
    for(int T = 1 ; T<= n ; ++ T) {
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
        if(!k) {
            printf("Case %d: 0\n", T);
            continue;
        }
        #define ll long long
        ll ans = 0, tmp = 0;
        b /= k, d /= k;
        for(int i = 1 ; i <= min(b, d) ; ++ i)
            ans += (ll) mu[i] * (b / i) * (d / i),
            tmp += (ll) mu[i] * (min(b, d) / i) * (min(b, d) / i);
        ans = ans - tmp / 2;
        printf("Case %d: %lld\n", T, ans);
    }
}

