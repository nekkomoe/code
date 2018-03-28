#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long ll;

const int N = 200010 * 4;

int n, m, s, t;

int head[N], w[N], rest[N], to[N], tot = 1;

void add(int u, int v, int w) {
    to[++ tot] = v, :: w[tot] = w, rest[tot] = head[u], head[u] = tot;
}

int sta[N], tp;

bool cmp(int a, int b) {
    return w[a] <  w[b];
}

struct E {
    int u, w;
};

vector<E> G[N];

const ll inf = 1ll << 60;

ll dis[N];

typedef pair<ll, int> T;

priority_queue<T, vector<T>, greater<T> > pq;

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, u, v, w ; i <= m ; ++ i) {
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w), add(v, u, w);
    }
    s = tot + 1, t = s + 1;
    for(int i = 1 ; i <= n ; ++ i) {
        tp = 0;
        for(int j = head[i] ; j ; j = rest[j]) {
            sta[++ tp] = j;
        }
        sort(sta + 1, sta + 1 + tp, cmp);
        for(int j = 1 ; j <= tp ; ++ j) {
            int u = sta[j], v = sta[j + 1];
            if(to[u] == n) G[u].push_back((E) { t, w[u] });
            if(i == 1) G[s].push_back((E) { u, w[u] });
            G[u ^ 1].push_back((E) { u, w[u] });
            if(j < tp) {
                G[u].push_back((E) { v, w[v] - w[u] });
                G[v].push_back((E) { u, 0 });
            }
        }
    }
    for(int i = 2 ; i <= t ; ++ i) dis[i] = inf;
    pq.push(make_pair(0, s));
    dis[s] = 0;
    while(pq.size()) {
        int u = pq.top().second; ll w = pq.top().first; pq.pop();
        if(w > dis[u]) continue;
        for(int i = 0 ; i < G[u].size() ; ++ i) {
            E &e = G[u][i];
            int v = e.u, w = e.w;
            if(dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pq.push(make_pair(dis[v], v));
            }
        }
    }
    printf("%lld\n", dis[t]);
}

