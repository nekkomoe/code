#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e6 + 10;

int n, k, ms, me;
int s[N], e[N];
ll ans;
int S, T;
int head[N], rest[N], from[N], to[N], tot = 1;
ll flow[N], cost[N], dis[N];
const ll inf = 0x3f3f3f3f3f3f3f3fll;
int pre[N], inq[N];

void add_sub(int u, int v, ll f, ll c) {
    from[++ tot] = u, to[tot] = v, flow[tot] = f, cost[tot] = c, rest[tot] = head[u], head[u] = tot;
}
void add(int u, int v, ll f, ll c) {
    add_sub(u, v, f, c), add_sub(v, u, 0, -c);
}

int bfs() {
    for(int i = 1 ; i <= 3000 ; ++ i) {
        dis[i] = -inf;
        pre[i] = 0;
    }
    queue<int> q;
    dis[S] = 0, q.push(S), inq[S] = 1;
    while(q.size()) {
        int u = q.front(); q.pop();
        inq[u] = 0;
        // printf("vis %d\n", u);
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            // printf("v = %d, %d\n", v, flow[i]);
            if(flow[i] && dis[v] < dis[u] + cost[i]) {
                dis[v] = dis[u] + cost[i];
                pre[v] = i;
                if(!inq[v]) {
                    q.push(v);
                }
            }
        }
    }
    // printf("dis[T] = %lld, %lld\n", dis[T], inf);
    return dis[T] != -inf;
}

int pos[N];

int main() {
    scanf("%d%d%d%d", &n, &k, &ms, &me);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &s[i]);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &e[i]);
        ans += e[i];
    }
    S = 3000, T = S - 1;

    add(S, 1, ms, 0);

    for(int i = 1 ; i <= n ; ++ i) {
        add(max(1, (i - k) * 2 + 1), min((n - k + 1) * 2 + 1, i * 2 + 1), 1, s[i] - e[i]);
        pos[i] = tot;
    }

    for(int i = 1 ; i <= n - k + 1 ; ++ i) {
        add(2 * i, 2 * i - 1, inf, 0);
        add(2 * i, 2 * i + 1, inf, 0);
        add(S, 2 * i, k - ms - me, 0);
        if(i < n - k + 1) {
            add(2 * i + 1, T, k - ms - me, 0);
        } else {
            add(2 * i + 1, T, k - me, 0);
        }
    }

    while(bfs()) {
        ll mn = inf;
        for(int i = pre[T] ; i ; i = pre[from[i]]) {
            mn = min(mn, flow[i]);
        }
        ans += dis[T] * mn;
        for(int i = pre[T] ; i ; i = pre[from[i]]) {
            flow[i] -= mn, flow[i ^ 1] += mn;
        }
    }
    printf("%lld\n", ans);
    for(int i = 1 ; i <= n ; ++ i) {
        putchar(flow[pos[i]] ? 'S' : 'E');
    }
}
