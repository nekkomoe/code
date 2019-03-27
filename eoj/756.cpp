#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 110, mod = 1e9 + 7;

int n, m, k; ll len;
struct E { int v, w; }; vector<E> g[N];

int cho[N];

ll mxdis;

ll dfs(int u, int fa) {
    ll mx = cho[u] ? 0 : 0xcfcfcfcfcfcfcfcf;
    for(E e: g[u]) {
        int v = e.v, w = e.w;
        if(v == fa) continue;
        ll tmp = dfs(v, u) + w;
        mxdis = max(mxdis, mx + tmp);
        mx = max(mx, tmp);
    }
    return mx;
}

void runprog() {
    int ans = 0;
    for(int s = 0 ; s < (1 << n) ; ++ s) {
        int cnt = 0;
        for(int i = 0 ; i < n ; ++ i) {
            cnt += (s >> i) & 1;
            cho[i + 1] = 0;
        }
        if(cnt != k) continue;
        for(int i = 0 ; i < n ; ++ i) {
            if((s >> i) & 1) {
                cho[i + 1] = 1;
            }
        }
        mxdis = 0; dfs(1, 0);
        ans += mxdis <= len;
    }
    printf("%d\n", ans);
}

namespace beimabao {
    const int N = 55;
    int K, LEN, sz[N];
    ll f[N][N][N], g[N][N][N];
    int dep[N], mxdep[N];

    void dfs(int u, int fa) {
        dep[u] = dep[fa] + 1;
        f[u][1][dep[u]] = 1;
        sz[u] = 1;
        for(E e: :: g[u]) {
            int v = e.v;
            if(v == fa) continue;
            dfs(v, u);
            sz[u] += sz[v];

            for(int i = 0 ; i <= n ; ++ i) {
                for(int j = 0 ; j <= n ; ++ j) {
                    g[u][i][j] = f[u][i][j];
                }
            }

            for(int j = 0 ; j <= n ; ++ j) {
                for(int k = 0 ; k <= n ; ++ k) {
                    for(int a = 0 ; a <= j ; ++ a) {
                        if(j - a <= sz[v]) {
                            for(int p = 0 ; p <= k - 1 ; ++ p) {
                                if(k + p - 2 * dep[u]<= LEN) {
                                    (g[u][j][k] += f[u][a][k] * f[v][j - a][p] % mod) %= mod;
                                }
                            }
                            for(int p = 0 ; p <= k ; ++ p) {
                                if(p + k - 2 * dep[u] <= LEN) {
                                    (g[u][j][k] += f[u][a][p] * f[v][j - a][k] % mod) %= mod;
                                }
                            }
                        }
                    }
                    (g[u][j][k] += f[v][j][k]) %= mod;
                }
            }

            for(int i = 0 ; i <= n ; ++ i) {
                for(int j = 0 ; j <= n ; ++ j) {
                    f[u][i][j] = g[u][i][j];
                }
            }
        }
    }

    void runprog() {
        scanf("%d%d", &K, &LEN);
        dfs(1, 0);
        ll ans = 0;
        for(int i = 0 ; i <= n ; ++ i) {
            (ans += f[1][K][i]) %= mod;
        }
        printf("%lld\n", ans);
    }
}

ll ed[N], s[N];

namespace seq {

    ll C[110][110];

    void runprog() {

        C[0][0] = 1;
        for(int i = 1 ; i <= 100 ; ++ i) {
            C[i][0] = 1;
            for(int j = 1 ; j <= i ; ++ j) {
                C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
            }
        }

        for(int i = 1 ; i < n ; ++ i) {
            s[i] = s[i - 1] + ed[i];
        }
        while(m --) {
            int k; ll len; scanf("%d%lld", &k, &len);
            ll ans = 0;
            for(int i = 1, j = 1 ; i <= n ; ++ i) {
                if(j < i) j = i;
                while(j + 1 <= n && s[j] - s[i - 1] <= len) {
                    ++ j;
                }
                if(s[j - 1] - s[i - 1] > len) continue;
                if(j - i + 1 - 1 < 0 || k - 1 < 0) continue;
                (ans += C[j - i + 1 - 1][k - 1]) %= mod;
            }
            printf("%lld\n", ans);
        }
    }
}

const ll inf = 0x3f3f3f3f3f3f3f3fll;
ll dis[N][N];
typedef pair<ll, ll> pr;

pr operator + (pr a, pr b) {
    return dis[a.first][a.second] > dis[b.first][b.second] ? a : b;
}

ll f[N][N][N];
vector<pair<ll, ll> > res[N];
void upd(ll &x, ll y) {
    (x += y) %= mod;
}

void fafarunprog() {
    for(int k = 1 ; k <= n ; ++ k) {
        for(int i = 1 ; i <= n ; ++ i) {
            for(int j = 1 ; j <= n ; ++ j) {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
    for(int i = 0 ; i <= n ; ++ i) dis[0][i] = dis[i][0] = -1;

    f[0][0][0] = 1;
    for(int i = 0 ; i < n ; ++ i) {
        for(int j = i ; j >= 0 ; -- j) {
            for(int a = 0 ; a <= i ; ++ a) {
                for(int b = a ; b <= i ; ++ b) {
                    pr mn = pr(a, b) + pr(a, i + 1) + pr(b, i + 1);
                    upd(f[j + 1][mn.first][mn.second], f[j][a][b]);
                }
            }
        }
    }

    for(int i = 0 ; i <= n ; ++ i) {
        for(int a = 1 ; a <= n ; ++ a) {
            for(int b = a ; b <= n ; ++ b) {
                res[i].push_back(pr(dis[a][b], f[i][a][b]));
            }
        }
        sort(res[i].begin(), res[i].end());
        for(int j = 1 ; j < res[i].size() ; ++ j) {
            upd(res[i][j].second, res[i][j - 1].second);
        }
    }

    while(m --) {
        int k; ll len; scanf("%d%lld", &k, &len);
        auto it = upper_bound(res[k].begin(), res[k].end(), pr(len, inf));
        if(it == res[k].begin()) puts("0");
        else printf("%lld\n", (-- it) -> second);
    }
}

int main() {
//    freopen("catering.in", "r", stdin);
//    freopen("catering.out", "w", stdout);
    scanf("%d%d", &n, &m);
    memset(dis, 0x3f, sizeof dis);
    for(int i = 1, u, v, w ; i < n ; ++ i) {
        scanf("%d%d%d", &u, &v, &w);
        g[u].push_back((E) { v, w });
        g[v].push_back((E) { u, w });
        dis[u][v] = dis[v][u] = w;
        ed[i] = w;
    }
    // if(n <= 10) {
    //     while(m --) {
    //         scanf("%d%lld", &k, &len);
    //         runprog();
    //     }
    // } else if(n <= 50 && m <= 1) {
    //     beimabao :: runprog();
    // } else {
    //     seq :: runprog();
    // }
    fafarunprog();
}
