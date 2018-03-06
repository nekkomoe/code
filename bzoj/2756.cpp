%:pragma GCC optimize(2)
%:pragma GCC optimize(3)

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

//#define int ll

const int N = 2e6 + 10;

const ll inf = 1ll << 60;

int n, m, s, t, head[2010], rest[N], to[N], tot = 1, mv[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

ll dis[2010], flow[N];

void add(int u, int v, ll f) {
    to[++ tot] = v, flow[tot] = f, rest[tot] = head[u], head[u] = tot;
}

void ins(int u, int v, ll f) {
    add(u, v, f), add(v, u, 0);
}

void ins2(int u, int v, ll f) {
    ins(u, v, f), ins(v, u, f);
}

bool bfs() {
    queue<int> q;
    memset(dis, -1, sizeof dis);
    dis[s] = 0;
    q.push(s);
    while(q.size()) {
        int u = q.front();
        q.pop();
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(flow[i] && dis[v] == -1) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    return dis[t] != -1;
}

ll dfs(int u, ll f) {
    if(u == t) return f;
    ll use = 0;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!flow[i] || dis[v] != dis[u] + 1) continue;
        ll a = dfs(v, min(f - use, flow[i]));
        use += a, flow[i] -= a, flow[i ^ 1] += a;
        if(use == f) break;
    }
    if(!use) dis[u] = -1;
    return use;
}

ll dinic() {
    ll res = 0;
    while(bfs()) res += dfs(s, inf);
    return res;
}

ll a[50][50];

int id(int i, int j) {
    return (i - 1) * m + j;
}

int check(ll x) {
    memset(head, 0, sizeof head), tot = 1;
    ll cnt = 0;
    s = 2001, t = s + 1;
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            if((i + j) & 1) {
                ins(s, id(i, j), x - a[i][j]);
                cnt += x - a[i][j];
                for(int k = 0 ; k < 4 ; ++ k) {
                    int ii = i + mv[k][0], jj = j + mv[k][1];
                    if( 1 <= ii && ii <= n && 1 <= jj && jj <= m ) {
                        ins(id(i, j), id(ii, jj), inf);
                    }
                }
            } else {
                ins(id(i, j), t, x - a[i][j]);
            }
        }
    }
    return cnt == dinic();
}

void sol() {
    ll wn = 0, bn = 0, ws = 0, bs = 0, mx = 0;
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            scanf("%lld", &a[i][j]);
            mx = max(mx, a[i][j]);
            if((i + j) & 1) {
                wn ++, ws += a[i][j];
            } else {
                bn ++, bs += a[i][j];
            }
        }
    }
    if(wn == bn && ws != bs) return puts("-1"), void();
    else if(wn == bn) {
        ll l = mx, r = 1ll << 50;
        while(l <= r) {
            ll mid = (l + r) >> 1;
            if(check(mid)) r = mid - 1; else l = mid + 1;
        }
        printf("%lld\n", l * wn - ws);
    } else {
        ll x = (bs - ws) / (bn - wn);
        if(x < mx) puts("-1");
        else if(check(x)) printf("%lld\n", x * wn - ws);
        else puts("-1");
    }
    
}

signed main() {
    int T;
    scanf("%d", &T);
    while(T --) {
        sol();
    }    
}
