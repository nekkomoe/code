#include <bits/stdc++.h>

using namespace std;

const int N = 50010;

int n, a, b, c, d, k, mu[N], vis[N], prime[N], p;

void build() {
    mu[1] = 1;
    for(int i = 2 ; i <= 50000 ; ++ i) {
        if(!vis[i]) prime[++ p] = i, mu[i] = -1;
        for(int j = 1 ; j <= p ; ++ j) {
            if(i * prime[j] > 50000) break;
            vis[i * prime[j]] = 1;
            if(i % prime[j]) mu[i * prime[j]] = -mu[i];
            else break;
        }
    }
    for(int i = 1 ; i <= 50000 ; ++ i) mu[i] += mu[i - 1];
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

int main() {
    scanf("%d", &n);
    build();
    while(n --) {
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
        printf("%d\n", sol(b, d) - sol(a - 1, d) - sol(b, c - 1) + sol(a - 1, c - 1));
    }
}
