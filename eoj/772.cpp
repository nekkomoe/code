#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
%:pragma GCC optimize("Ofast")
%:pragma GCC optimize("inline")
%:pragma GCC optimize("-fgcse")
%:pragma GCC optimize("-fgcse-lm")
%:pragma GCC optimize("-fipa-sra")
%:pragma GCC optimize("-ftree-pre")
%:pragma GCC optimize("-ftree-vrp")
%:pragma GCC optimize("-fpeephole2")
%:pragma GCC optimize("-ffast-math")
%:pragma GCC optimize("-fsched-spec")
%:pragma GCC optimize("unroll-loops")
%:pragma GCC optimize("-falign-jumps")
%:pragma GCC optimize("-falign-loops")
%:pragma GCC optimize("-falign-labels")
%:pragma GCC optimize("-fdevirtualize")
%:pragma GCC optimize("-fcaller-saves")
%:pragma GCC optimize("-fcrossjumping")
%:pragma GCC optimize("-fthread-jumps")
%:pragma GCC optimize("-funroll-loops")
%:pragma GCC optimize("-fwhole-program")
%:pragma GCC optimize("-freorder-blocks")
%:pragma GCC optimize("-fschedule-insns")
%:pragma GCC optimize("inline-functions")
%:pragma GCC optimize("-ftree-tail-merge")
%:pragma GCC optimize("-fschedule-insns2")
%:pragma GCC optimize("-fstrict-aliasing")
%:pragma GCC optimize("-fstrict-overflow")
%:pragma GCC optimize("-falign-functions")
%:pragma GCC optimize("-fcse-skip-blocks")
%:pragma GCC optimize("-fcse-follow-jumps")
%:pragma GCC optimize("-fsched-interblock")
%:pragma GCC optimize("-fpartial-inlining")
%:pragma GCC optimize("no-stack-protector")
%:pragma GCC optimize("-freorder-functions")
%:pragma GCC optimize("-findirect-inlining")
%:pragma GCC optimize("-fhoist-adjacent-loads")
%:pragma GCC optimize("-frerun-cse-after-loop")
%:pragma GCC optimize("inline-small-functions")
%:pragma GCC optimize("-finline-small-functions")
%:pragma GCC optimize("-ftree-switch-conversion")
%:pragma GCC optimize("-foptimize-sibling-calls")
%:pragma GCC optimize("-fexpensive-optimizations")
%:pragma GCC optimize("-funsafe-loop-optimizations")
%:pragma GCC optimize("inline-functions-called-once")
%:pragma GCC optimize("-fdelete-null-pointer-checks")

#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 3010, mod = 998244353; 

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

int n;
int a[N][N + 5];

vector<pair<int, int> > g[N];
int deg[N], p[N], rev[N];
struct E {
    int u, v, w;
};
vector<E> ed;

int main() {
// #ifdef ONLINE_JUDGE
//     freopen("wander.in", "r", stdin);
//     freopen("wander.out", "w", stdout);
// #else
//     freopen("data.in", "r", stdin);
// #endif
    scanf("%d", &n);
    
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%*d%*d");
        p[i] = i;
    }

    int m; scanf("%d", &m);
    for(int i = 1, u, v, w ; i <= m ; ++ i) {
        scanf("%d%d%d", &u, &v, &w);
        ed.push_back((E) { u, v, w });
        ++ deg[u], ++ deg[v];
    }

    srand((unsigned long long) new char);
    random_shuffle(p + 1, p + 1 + n);
    sort(p + 1, p + 1 + n, [&](int a, int b) { return a == b ? 0 : deg[a] == deg[b] ? rand() & 1 : deg[a] < deg[b]; });
    
    for(auto e: ed) {
        int u = e.u, v = e.v, w = e.w;
        u = p[u], v = p[v];
        g[u].push_back(make_pair(v, w));
        g[v].push_back(make_pair(u, w));
    }


    for(int i = 1 ; i <= n ; ++ i) {
        a[i][i] = 1;
        ll coef = pw(g[i].size(), mod - 2);
        for(auto t: g[i]) {
            int v = t.first, w = t.second;
            a[i][v] = (mod - coef) % mod;
            (a[i][n + 1] += 1ll * w * coef % mod) %= mod;
        }
    }
    for(int i = 1 ; i <= n + 1 ; ++ i) {
        a[p[n]][i] = 0;
    } a[p[n]][p[n]] = 1;

    for(int i = 1 ; i <= n ; ++ i) {
        int cho = i;
        for(int j = i + 1 ; j <= n ; ++ j) {
            if(a[j][i] > a[cho][i]) {
                cho = j;
            }
        }
        if(cho != i) {
            for(int j = i ; j <= n + 1 ; ++ j) {
                swap(a[i][j], a[cho][j]);
            }
        }
        int y = pw(a[i][i], mod - 2);
        for(int j = i + 1 ; j <= n ; ++ j) {
            if(a[j][i]) {
                int x = 1ll * a[j][i] * y % mod;
                for(int k = i ; k <= n + 1 ; ++ k) {
                    a[j][k] = (mod + a[j][k] - 1ll * a[i][k] * x % mod) % mod;
                }
            }
        }
    }
    
    for(int i = n ; i >= 1 ; -- i) {
        int x = pw(a[i][i], mod - 2);
        a[i][n + 1] = (ll) a[i][n + 1] * x % mod;
        for(int j = i - 1 ; j >= 1 ; -- j) {
            (a[j][n + 1] -= 1ll * a[j][i] * a[i][n + 1] % mod) %= mod;
        }
    }

    ll ans = a[p[1]][n + 1];
    if(ans < 0) ans += mod;
    printf("%d\n", ans);
}
