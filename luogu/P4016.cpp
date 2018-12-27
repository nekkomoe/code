#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e6 + 10, inf = 0x3f3f3f3f;

int head[N], rest[N], from[N], to[N], w[N], cost[N], tot = 1;

void sig(int u, int v, int w, int cost) {
    from[++ tot] = u, to[tot] = v, :: w[tot] = w, :: cost[tot] = cost, rest[tot] = head[u], head[u] = tot;
}
void add(int u, int v, int w, int cost) {
    sig(u, v, w, cost), sig(v, u, 0, -cost);
}

int n, a[N];

int dis[N], S, T, pre[N], inq[N];
int spfa() {
    for(int i = 1 ; i <= T ; ++ i) dis[i] = inf, pre[i] = 0;
    dis[S] = 0; queue<int> q; q.push(S); inq[S] = 1;
    while(q.size()) {
        int u = q.front(); q.pop(); inq[u] = 0;
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(w[i] && dis[v] > dis[u] + cost[i]) {
                dis[v] = dis[u] + cost[i];
                pre[v] = i;
                if(!inq[v]) q.push(v), inq[v] = 1;
            }
        }
    }
    return dis[T] != inf;
}

int get() {
    int res = 0;
    while(spfa()) {
        int mn = inf;
        for(int i = pre[T] ; i ; i = pre[from[i]]) mn = min(mn, w[i]);
        for(int i = pre[T] ; i ; i = pre[from[i]]) w[i] -= mn, w[i ^ 1] += mn;
        res += mn * dis[T];
    }
    return res;
}

int main() {
    scanf("%d", &n); int sum = 0;
    S = n + 1, T = S + 1;
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]), sum += a[i];
    assert(sum % n == 0);
    int avg = sum / n;
    for(int i = 1 ; i <= n ; ++ i) {
        if(i + 1 <= n) add(i, i + 1, inf, 1);
        if(i - 1 >= 1) add(i, i - 1, inf, 1);
        if(a[i] - avg >= 0) {
            add(S, i, a[i] - avg, 0);
        } else {
            add(i, T, avg - a[i], 0);
        }
    }
    add(1, n, inf, 1), add(n, 1, inf, 1);
    printf("%d\n", get());
}

