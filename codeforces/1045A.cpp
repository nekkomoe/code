#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e6 + 10;

int n, m, cnt;

int head[N], rest[N], to[N], flow[N], tot = 1, S, T;
int dis[N];

bool fwd[N];

void add_sig(int u, int v, int w) {
    to[++ tot] = v, flow[tot] = w, rest[tot] = head[u], head[u] = tot;
}

void add(int u, int v, int w) {
    add_sig(u, v, w);
    fwd[tot] = 1;
    add_sig(v, u, 0);
}

int bfs() {
    for(int i = 1 ; i <= cnt ; ++ i) dis[i] = -1;
    queue<int> q;
    q.push(S), dis[S] = 1;
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(flow[i] && dis[v] == -1) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    return dis[T] != -1;
}

int dfs(int u, int f) {
    if(u == T || !f) return f;
    int use = 0;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(dis[v] == dis[u] + 1 && flow[i]) {
            int a = dfs(v, min(flow[i], f - use));
            use += a, flow[i] -= a, flow[i ^ 1] += a;
            if(use == f) break;
        }
    }
    if(!use) dis[u] = -1;
    return use;
}

int mxflow() {
    int res = 0;
    while(bfs()) res += dfs(S, 0x3f3f3f3f);
    return res;
}

int vis[N], tmp[N], bel[N];

#define lc (id << 1)
#define rc (id << 1 | 1)

void build(int id, int l, int r) {
    cnt = max(cnt, id);
    int mid = (l + r) >> 1;
    if(l == r) {
        tmp[l] = id;
        bel[id] = l;
    } else {
        build(lc, l, mid), build(rc, mid + 1, r);
        add(id, lc, 0x3f3f3f3f), add(id, rc, 0x3f3f3f3f);
    }
}

void ask(int id, int l, int r, int ql, int qr, int src) {
    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) {
        add(src, id, 1);
    } else if(qr <= mid) {
        ask(lc, l, mid, ql, qr, src);
    } else if(ql >= mid + 1) {
        ask(rc, mid + 1, r, ql, qr, src);
    } else {
        ask(lc, l, mid, ql, mid, src);
        ask(rc, mid + 1, r, mid + 1,qr, src);
    }
}

int pos[N], rem[N];

vector<pair<int, int> > output;

struct T {
    int ty, a, b, c;
} inp[N];

int go(int u, int fr = 0) {
    if(bel[u]) {
        int res = bel[u];
        bel[u] = 0;
        return res;
    }
    for(int &i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(flow[i] != 1 && flow[i] != 0x3f3f3f3f && fwd[i]) {
            flow[i] ++;
            return go(v, u);
        }
    }
    return -1;
}

int poi[N];
int main() {
    int ans = 0;
    scanf("%d%d", &n, &m);
    build(1, 1, m);
    S = ++ cnt, T = ++ cnt;
    for(int i = 1 ; i <= n ; ++ i) {
        pos[i] = ++ cnt;
        int ty; scanf("%d", &ty);
        inp[i].ty = ty;
        if(ty == 0) {
            int k; scanf("%d", &k);
            for(int j = 1 ; j <= k ; ++ j) {
                int tar; scanf("%d", &tar);
                add(pos[i], tmp[tar], 1);
            }
            add(S, pos[i], 1);
        } else if(ty == 1) {
            int l, r; scanf("%d%d", &l, &r);
            ask(1, 1, m, l, r, pos[i]);
            add(S, pos[i], 1);
        } else {
            int a, b, c; scanf("%d%d%d", &a, &b, &c);
            vis[a] = vis[b] = vis[c] = 1;
            add(tmp[a], pos[i], 1);
            add(tmp[b], pos[i], 1);
            add(tmp[c], pos[i], 1);
            add(pos[i], T, 1);
            ans += 2;
            inp[i].a = a, inp[i].b = b, inp[i].c = c;
        }
    }
    for(int i = 1 ; i <= m ; ++ i) {
        if(!vis[i]) {
            add(tmp[i], T, 1);
        }
    }
    printf("%d\n", ans + mxflow());

    for(int i = head[S] ; i ; i = rest[i]) {
        int v = to[i];
        if(flow[i] == 0) {
            poi[v] = 1;
        }
    }

    for(int i = 1 ; i <= n ; ++ i) {
        if(inp[i].ty != 2) {
            if(poi[pos[i]]) {
                int tar = go(pos[i]);
                if(tar != -1) {
                    output.push_back(make_pair(i, tar));
                    rem[tar] = 1;
                }
            }
        }
    }

    for(int i = 1 ; i <= n ; ++ i) {
        if(inp[i].ty == 2) {
            int p = 0;
            if(!rem[inp[i].a] && p < 2) {
                ++ p;
                output.push_back(make_pair(i, inp[i].a));
            }
            if(!rem[inp[i].b] && p < 2) {
                ++ p;
                output.push_back(make_pair(i, inp[i].b));
            }
            if(!rem[inp[i].c] && p < 2) {
                ++ p;
                output.push_back(make_pair(i, inp[i].c));
            }
        }
    }

    for(int i = 0 ; i < output.size() ; ++ i) {
        printf("%d %d\n", output[i].first, output[i].second);
    }
}
