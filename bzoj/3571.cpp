#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
struct E { ll a, b, c; int u, v; } e[N];
struct P { ll x, y; P(ll x = 0, ll y = 0) : x(x), y(y) { } } ans, mnA, mnB;
bool operator < (P a, P b) {
    ll A = a.x * a.y, B = b.x * b.y;
    return A == B ? a.x < b.x : A < B;
}
P operator - (P a, P b) {
    return P(a.x - b.x, a.y - b.y);
}
ll operator * (P a, P b) {
    return a.x * b.y - b.x * a.y;
}

int n, m, id[100][100];

int head[N], rest[N], from[N], to[N], tot, dis[N], S, T, flow[N], cost[N];

void add_sig(int u, int v, int w, int c) {
    to[++ tot] = v, from[tot] = u, flow[tot] = w, cost[tot] = c, rest[tot] = head[u], head[u] = tot;
}

void add(int u, int v, int w, int c) {
    add_sig(u, v, w, c);
    add_sig(v, u, 0, -c);
}

int inq[N], pre[N], ed[N];

int spfa() {
    for(int i = 1 ; i <= T ; ++ i) dis[i] = 0x3f3f3f3f, pre[i] = 0;
    queue<int> q;
    dis[S] = 0, q.push(S), inq[S] = 1;
    while(q.size()) {
        int u = q.front(); q.pop(); inq[u] = 0;
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(flow[i] && dis[v] > dis[u] + cost[i]) {
                dis[v] = dis[u] + cost[i];
                pre[v] = i;
                if(!inq[v]) {
                    q.push(v);
                    inq[v] = 1;
                }
            }
        }
    }
    return dis[T] != 0x3f3f3f3f;
}

void getans() {
    for(int i = 1 ; i <= T ; ++ i) head[i] = 0;
    tot = 1;
    for(int i = 1 ; i <= m ; ++ i) {
        add(e[i].u, e[i].v, 1, e[i].c);
        ed[i] = tot;
        // printf("%d -> %d %lld\n", e[i].u, e[i].v, e[i].c);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        add(S, i, 1, 0);
        add(i + n, T, 1, 0);
        // printf("%d -> %d\n", S, i);
        // printf("%d -> %d\n", i + n, T);
    }
    int res = 0;
    while(spfa()) {
        // puts("END");

        int mn = 0x3f3f3f3f;
        for(int i = pre[T] ; i ; i = pre[from[i]]) {
            mn = min(mn, flow[i]);
        }
        res += mn * dis[T];
        for(int i = pre[T] ; i ; i = pre[from[i]]) {
            flow[i] -= mn, flow[i ^ 1] += mn;
        }
    }
    // printf("res = %d\n", res);
}

P neko() {
    P res;
    getans();
    for(int i = 1 ; i <= m ; ++ i) {
        if(flow[ed[i]]) {
            res.x += e[i].a;
            res.y += e[i].b;
        }
    }
    ans = min(ans, res);
    return res;
}

void sol(P A, P B) {
    for(int i = 1 ; i <= m ; ++ i) e[i].c = e[i].b * (A.x - B.x) + e[i].a * (B.y - A.y);
    P C = neko();
    if((B - A) * (C - A) <= 0) return ;
    sol(A, C), sol(C, B);
}

void runprog() {
    scanf("%d", &n);
    m = 0;

    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            id[i][j] = ++ m;
            e[id[i][j]].u = i;
            e[id[i][j]].v = j + n;
        }
    }

    S = m + 1, T = S + 1;

    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            scanf("%lld", &e[id[i][j]].a);
        }
    }

    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            scanf("%lld", &e[id[i][j]].b);
        }
    }

    for(int i = 1 ; i <= m ; ++ i) e[i].c = e[i].a;
    mnA = neko(), ans = mnA;
    
    for(int i = 1 ; i <= m ; ++ i) e[i].c = e[i].b;
    mnB = neko();

    sol(mnB, mnA);
    // printf("%lld %lld\n", ans.x, ans.y);
    printf("%lld\n", ans.x * ans.y);
}

int main() {
    int T; scanf("%d", &T);
    while(T --) {
        runprog();
    }
}
