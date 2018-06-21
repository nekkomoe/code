#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e6;
ll n, mu[N + 10];

bool mk[N + 10];

int pri[N + 10], tot;

map<int, ll> q;

ll getq(ll x) { return x <= N ? mu[x] : q[x]; }

void sol(ll x) {
    if(x <= N || q.find(x) != q.end()) return ;
    ll qx = x >= 1;
    for(ll i = 2, j ; i <= x ; i = j + 1) {
        j = x / (x / i);
        sol(x / i);
        qx -= getq(x / i) * (j - i + 1);
    }
    q[x] = qx;
}

ll getans(ll n) {
    if(n <= N) return mu[n];
    sol(n);
    return q[n];
}

int main() {
    mu[1] = 1;
    for(int i = 2 ; i <= N ; ++ i) {
        if(!mk[i]) mu[i] = -1, pri[++ tot] = i;
        for(int j = 1 ; j <= tot && (ll) i * pri[j] <= N ; ++ j) {
            mk[i * pri[j]] = 1;
            if(i % pri[j] == 0) break;
            mu[i * pri[j]] = -mu[i];
        }
        mu[i] += mu[i - 1];
    }
    ll l, r; scanf("%lld%lld", &l, &r);
    printf("%lld\n", getans(r) - getans(l - 1));
}
