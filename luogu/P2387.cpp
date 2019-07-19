// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2e6 + 10;
const ll inf = 0x3f3f3f3f3f3f3f3fll;

ll dis[N];
queue<int> q;
int inq[N], n, m;

struct E {
    int u, v, a, b;
} e[N];
bool operator < (E a, E b) {
    return a.a < b.a;
}
int head[N], rest[N], to[N], tot, w[N];
void add(int u, int v, int c) {
    to[++ tot] = v, w[tot] = c, rest[tot] = head[u], head[u] = tot;
}

int main() {
    ll ans = inf;
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%d%d%d%d", &e[i].u, &e[i].v, &e[i].a, &e[i].b);
    }
    sort(e + 1, e + 1 + m);
    for(int i = 1 ; i <= n ; ++ i) {
        dis[i] = inf;
    }
    dis[1] = 0;
    q.push(1);
    inq[1] = 1;
    for(int i = 1 ; i <= m ; ++ i) {
        add(e[i].u, e[i].v, e[i].b);
        add(e[i].v, e[i].u, e[i].b);
        q.push(e[i].u);
        inq[e[i].u] = 1;
        q.push(e[i].v);
        inq[e[i].v] = 1;
        while(q.size()) {
            int u = q.front(); q.pop();
            inq[u] = 0;
            for(int j = head[u] ; j ; j = rest[j]) {
                int v = to[j];
                if(dis[v] > max(dis[u], (ll) w[j])) {
                    dis[v] = max(dis[u], (ll) w[j]);
                    if(!inq[v]) {
                        q.push(v);
                        inq[v] = 1;
                    }
                }
            }
        }
        if(dis[n] != inf) {
            ans = min(ans, dis[n] + e[i].a);
        }
    }

    if(ans == inf) {
        puts("-1");
    } else {
        printf("%lld\n", ans);
    }
}
