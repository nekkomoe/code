#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1010, mod = 1e9 + 7;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

const ll inv2 = pw(2, mod - 2);

int n, m; vector<int> g[N];

struct F {
    ll f[1030];
    void fwt(int ty) { // 0: fwt, 1: ifwt
        for(int i = 2 ; i <= m ; i <<= 1) {
            for(int j = 0 ; j + i / 2 < m ; j += i) {
                for(int k = j ; k < j + i / 2 ; ++ k) {
                    ll u = f[k], v = f[k + i / 2];
                    if(ty == 0) {
                        f[k] = (u + v) % mod;
                        f[k + i / 2] = (u - v) % mod;
                    } else {
                        f[k] = (u + v) * inv2 % mod;
                        f[k + i / 2] = (u - v) * inv2 % mod;
                    }
                }
            }
        }
    }
    void clear() {
        memset(f, 0, sizeof f);
    }
    F() { clear(); }
} f[N], ans, zero;

F operator + (F a, F b) {
    F res;
    for(int i = 0 ; i < m ; ++ i) {
        res.f[i] = (a.f[i] + b.f[i]) % mod;
    }
    return res;
}

F operator * (F a, F b) {
    F res;
    for(int i = 0 ; i < m ; ++ i) {
        res.f[i] = a.f[i] * b.f[i] % mod;
    }
    return res;
}

void dfs(int u, int fa) {
    for(int i = 0 ; i < g[u].size() ; ++ i) {
        int v = g[u][i];
        if(v == fa) continue;
        dfs(v, u);
        f[u] = f[u] * (f[v] + zero);
    }
    ans = ans + f[u];
}

void sol() {
    cin >> n >> m; int _m = m;
    m = 1024;
    for(int i = 1, x ; i <= n ; ++ i) {
        g[i].clear();
        f[i].clear();
        cin >> x;
        f[i].f[x] = 1;
        f[i].fwt(0);
    }
    for(int i = 1, u, v ; i < n ; ++ i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    ans.clear();
    dfs(1, 0);
    ans.fwt(1);
    for(int i = 0 ; i < _m ; ++ i) {
        cout << (ans.f[i] % mod + mod) % mod << (i == _m - 1 ? '\n' : ' '); 
    }
}

int main() {
//    freopen("data.in", "r", stdin); 
    ios :: sync_with_stdio(0);
    
    m = 1024;
    zero.f[0] = 1;
    zero.fwt(0);
    
    int t; cin >> t;
    while(t --) sol();
}

