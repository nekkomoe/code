#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10, inf = 0x3f3f3f3f;
int ans;
int head[N], rest[N], from[N], to[N], tot, cnt, flow[N], cost[N];
int n, m, row[1010][1010], col[1010][1010];
int S, T, dis[N], inq[N], pre[N];

void sub(int u, int v, int fl, int co) {
    to[++ tot] = v, from[tot] = u, flow[tot] = fl, cost[tot] = co, rest[tot] = head[u], head[u] = tot;
}

void add(int u, int v, int fl, int co) {
    sub(u, v, fl, co);
    sub(v, u, 0, -co);
}

int bfs() {
    for(int i = 1 ; i <= cnt ; ++ i) {
        dis[i] = -inf;
        inq[i] = 0;
        pre[i] = 0;
    }
    queue<int> q;
    inq[S] = 1, dis[S] = 0, q.push(S);
    while(q.size()) {
        int u = q.front(); q.pop();
        inq[u] = 0;
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(flow[i] && dis[v] < dis[u] + cost[i]) {
                dis[v] = dis[u] + cost[i];
                pre[v] = i;
                if(!inq[v]) {
                    inq[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    return dis[T] != -inf;
}

int totfl;
int getans() {
    int res = 0;
    while(bfs()) {
        int mn = inf;
        for(int i = pre[T] ; i ; i = pre[from[i]]) {
            mn = min(mn, flow[i]);
        }
        for(int i = pre[T] ; i ; i = pre[from[i]]) {
            flow[i] -= mn, flow[i ^ 1] += mn;
        }
        res += mn * dis[T];
        totfl += mn;
    }
    return res;
}

int a[1010][1010], b[1010][1010], ban[1010][1010];

void runprog() {
    for(int i = 1 ; i <= cnt ; ++ i) {
        head[i] = 0;
    }
    ans = 0;
    tot = 1;
    cnt = 0;

    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            a[i][j] = ++ cnt;
            b[i][j] = ++ cnt;
            ban[i][j] = 0;
        }
    }
    S = ++ cnt, T = ++ cnt;

    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j < m ; ++ j) {
            scanf("%d", &row[i][j]);
        }
    }
    for(int i = 1 ; i < n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            scanf("%d", &col[i][j]);
        }
    }

    int totban = 0;
    scanf("%d", &totban);
    for(int i = 1, x, y ; i <= totban ; ++ i) {
        scanf("%d%d", &x, &y);
        ban[x][y] = 1;
    }

    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            if((i + j) % 2) {
                if(j + 1 <= m) {
                    add(a[i][j], b[i][j + 1], 1, row[i][j]);
                }
                if(j - 1 >= 1) {
                    add(a[i][j], b[i][j - 1], 1, row[i][j - 1]);
                }
            } else {
                if(i + 1 <= n) {
                    add(a[i][j], b[i + 1][j], 1, col[i][j]);
                }
                if(i - 1 >= 1) {
                    add(a[i][j], b[i - 1][j], 1, col[i - 1][j]);
                }
            }

            add(S, a[i][j], 1, 0);
            add(b[i][j], T, 1, 0);
            if(!ban[i][j]) {
                add(a[i][j], b[i][j], 1, 0);
            }
        }
    }

    totfl = 0;
    ans = getans();
    static int casetot = 0;
    if(totfl == n * m) {
        printf("Case #%d: %d\n", ++ casetot, ans);
    } else {
        printf("Case #%d: Impossible\n", ++ casetot);
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
