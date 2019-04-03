#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 16, mod = 1e9 + 7;

map<int, ll> mem[1 << 16];

struct E {
    int s, w;
} e[int(1e6)];

int n, m;
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

ll dfs(int inpS) {
    if(!inpS) return 1;
    int T = inpS >> n, S = inpS ^ (T << n);
    if(mem[S].count(T)) return mem[S][T];
    ll &res = mem[S][T];
    for(int i = 1 ; i <= m ; ++ i) {
        int t = e[i].s;
        if((t & inpS) == t && ((ll) t << 1) > inpS) {
            (res += dfs(inpS ^ t) * e[i].w % mod) %= mod;
        }
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    int tm = 0;
    while(m --) {
        int t, u, v, S, T; scanf("%d%d%d", &t, &u, &v);
        S = (1 << (u - 1)) | (1 << (v + n - 1));
        e[++ tm] = (E) { S, pw(2, mod - 2) };
        if(t) {
            scanf("%d%d", &u, &v);
            T = (1 << (u - 1)) | (1 << (v + n - 1));
            e[++ tm] = (E) { T, pw(2, mod - 2) };
            if(S & T) continue;
            e[++ tm] = (E) { S | T, (t == 1 ? 1 : mod - 1) * pw(4, mod - 2) % mod };
        }
    }
    m = tm;
    printf("%lld\n", (ll) (1ll << n) * dfs((1ll << (n + n)) - 1) % mod);
}
