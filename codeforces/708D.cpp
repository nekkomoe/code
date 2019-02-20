#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e6 + 10;

int n, m;
const ll inf = 0x3f3f3f3f3f3f3f3fll;
int head[N], rest[N], from[N], to[N], tot = 1, S, T, inq[N], pre[N];
ll flow[N], cost[N], dis[N];

void addsig(int u, int v, ll f, ll c) {
    to[++ tot] = v, from[tot] = u, flow[tot] = f, cost[tot] = c, rest[tot] = head[u], head[u] = tot;
}

void add(int u, int v, ll f, ll c) {
    addsig(u, v, f, c), addsig(v, u, 0, -c);
}

int spfa() {
    queue<int> q;
    for(int i = 1 ; i <= T ; ++ i) dis[i] = inf, pre[i] = 0;
    dis[S] = 0, q.push(S), inq[S] = 1;
    while(q.size()) {
        int u = q.front(); q.pop(); inq[u] = 0;
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(dis[v] > dis[u] + cost[i] && flow[i]) {
                dis[v] = dis[u] + cost[i];
                pre[v] = i;
                if(!inq[v]) {
                    q.push(v);
                    inq[v] = 1;
                }
            }
        }
    }
    return dis[T] != inf;
}

ll ans;
ll getmax() {
    ll res = 0;
    while(spfa()) {
        ll mn = inf;
        for(int i = pre[T] ; i ; i = pre[from[i]]) mn = min(mn, flow[i]);
        res += mn * dis[T];
        for(int i = pre[T] ; i ; i = pre[from[i]]) flow[i] -= mn, flow[i ^ 1] += mn;
    }
    return res;
}
int d[N];

int main() {
    scanf("%d%d", &n, &m), S = n + 1, T = S + 1;
    for(int i = 1, u, v, c, f ; i <= m ; ++ i) {
        scanf("%d%d%d%d", &u, &v, &c, &f);
        d[u] -= f, d[v] += f;
        if(f > c) {
            ans += f - c;
            add(v, u, f - c, 0);
            add(v, u, c, 1);
            add(u, v, inf, 2);
        } else {
            add(v, u, f, 1);
            add(u, v, c - f, 1);
            add(u, v, inf, 2);
        }
    }
    add(n, 1, inf, 0);
    for(int i = 1 ; i <= n ; ++ i) {
        if(d[i] > 0) {
            add(S, i, d[i], 0);
        } else {
            add(i, T, -d[i], 0);
        }
    }
    printf("%lld\n", ans + getmax());
}

