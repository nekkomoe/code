#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

const int inf = 0x3f3f3f3f;

int day, p, m, f, n, s, x[N], y[N], S, T, r[N];

int head[N], rest[N], from[N], to[N], flow[N], cost[N], tot = 1;

void sub(int u, int v, int f, int c) {
    from[++ tot] = u, to[tot] = v, flow[tot] = f, cost[tot] = c, rest[tot] = head[u], head[u] = tot;
}

void add(int u, int v, int f, int c) {
    sub(u, v, f, c), sub(v, u, 0, -c);
}

int dis[N], inq[N], pre[N];

queue<int> q;

int spfa() {
    for(int i = 1 ; i <= T ; ++ i) dis[i] = inf, pre[i] = 0;
    dis[S] = 0;
    q.push(S);
    inq[S] = 1;
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
    return dis[T] != inf;
}

int sol() {
    int res = 0;

    while(spfa()) {
        int mn = inf;
        for(int i = pre[T] ; ; i = pre[from[i]]) {
            mn = min(mn, flow[i]);
            if(from[i] == S) break;
        }
        for(int i = pre[T] ; ; i = pre[from[i]]) {
            flow[i] -= mn, flow[i ^ 1] += mn;
            if(from[i] == S) break;
        }
        res += mn * dis[T];
    }

    return res;
}

int main() {
    scanf("%d%d%d%d%d%d", &day, &p, &m, &f, &n, &s);
    for(int i = 1 ; i <= day ; ++ i) scanf("%d", &r[i]), x[i] = i, y[i] = i + day;
    S = y[day] + 1, T = S + 1;
    for(int i = 1 ; i <= day ; ++ i) {
        add(S, x[i], r[i], 0);
        if(i + 1 <= day) add(x[i], x[i + 1], inf, 0);
        add(y[i], T, r[i], 0);
        add(S, y[i], inf, p);
        if(i + m <= day) add(x[i], y[i + m], inf, f);
        if(i + n <= day) add(x[i], y[i + n], inf, s);
    }
    printf("%d\n", sol());
}
