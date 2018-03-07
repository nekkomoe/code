#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 5e4 + 5;

int n, a, b, c, d, k, mu[N], vis[N], prime[N], p, T;

void build() {
    mu[1] = 1;
    for(int i = 2 ; i <= N - 5 ; ++ i) {
        if(!vis[i]) prime[++ p] = i, mu[i] = -1;
        for(int j = 1 ; j <= p ; ++ j) {
            if(i * prime[j] > N - 5) break;
            vis[i * prime[j]] = 1;
            if(i % prime[j]) mu[i * prime[j]] = -mu[i];
            else break;
        }
    }
}

ll sol(ll n) {
    ll sum = 0;
    for(ll i = 1 ; i <= (ll) sqrt(n) ; ++ i) {
        sum += n / (i * i) * mu[i];
    }
    return sum;
}

int main() {
    scanf("%d", &T);
    build();
    while(T --) {
        scanf("%d", &k);
        ll l = k, r = 2e9, ans;
        while(l <= r) {
            ll mid = (l + r) >> 1;
            if(sol(mid) >= k) ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        printf("%lld\n", ans);
    }
}
