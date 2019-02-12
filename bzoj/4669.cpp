%:pragma GCC optimize(2)

#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 3e6 + 10, M = N;

int n, m, k;

int head[N], rest[M], from[M], to[M], cost[M], tot, pre[N], flow[M];
inline void add_sig(int u, int v, int w, int co) {
    ++ tot, from[tot] = u, to[tot] = v, cost[tot] = co, flow[tot] = w, rest[tot] = head[u], head[u] = tot;
}
inline void add(int u, int v, int w, int co) {
    add_sig(u, v, w, co), add_sig(v, u, 0, -co);
}

int dis[N];

struct E { int u, v, w; } e[N];

int sta[N][2], top;

int spfa() {
    for(int i = 1 ; i <= n ; ++ i) {
        dis[i] = 0x3f3f3f3f;
        pre[i] = 0;
    }
    queue<int> q;
    q.push(1), dis[1] = 0;
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(dis[v] > dis[u] + cost[i] && flow[i]) {
                dis[v] = dis[u] + cost[i];
                pre[v] = i;
                q.push(v);
            }
        }
    }
    return dis[n] != 0x3f3f3f3f;
}

int check(ll ele) {
    ll res = 0;
    for(int i = 1 ; i <= top && res < k ; ++ i) {
        res += max(0ll, (ele - sta[i][0] + 1) * sta[i][1]);
    }
    return res >= k;
}

void runprog() {    
    for(int i = 1 ; i <= n ; ++ i) {
        head[i] = 0;
    }
    tot = 1;
    top = 0;

    for(int i = 1 ; i <= m ; ++ i) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        add(u + 1, v + 1, w, 1);
    }

    if(!k) {
        puts("0");
        return ;
    }

    while(spfa()) {
        int mn = 0x3f3f3f3f;
        for(int i = pre[n] ; i ; i = pre[from[i]]) {
            mn = min(mn, flow[i]);
        }
        for(int i = pre[n] ; i ; i = pre[from[i]]) {
            flow[i] -= mn;
            flow[i ^ 1] += mn;
        }
        // printf("%d %d\n", dis[n], mn);
        sta[++ top][0] = dis[n];
        sta[top][1] = mn;
    }

    ll l = 0, r = 1e15, ans = -1;

    while(l <= r) {
        ll mid = (l + r) >> 1;
        if(check(mid)) {
            r = mid - 1;
            ans = mid;
        } else {
            l = mid + 1;
        }
    }

    if(ans == -1) {
        puts("No solution");
    } else {
        printf("%lld\n", ans);
    }
}

int main() {
    while(scanf("%d%d%d", &n, &m, &k) == 3) {
        runprog();
    }
}
