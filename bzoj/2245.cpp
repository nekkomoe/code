#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define int ll

const int N = 210000;

const int inf = 0x3f3f3f3f3f3f3f3fll;

int n, m, s, t, ansf, ansc;

int head[N], rest[N], from[N], to[N], flow[N], cost[N], tot;

int dis[N], inq[N], pre[N];

deque<int> q;

void add(int u, int v, int f, int c) {
    from[tot] = u;
    to[tot] = v;
    flow[tot] = f;
    cost[tot] = c;
    rest[tot] = head[u];
    head[u] = tot ++;
}

void insert(int u, int v, int f, int c) {
    add(u, v, f, c);
    add(v, u, 0, -c);
}

int spfa() {
    memset(dis, 0x3f, sizeof(dis));
    memset(pre, 0xff, sizeof(pre));
    q.push_back(s);
    dis[s] = 0;
    inq[s] = 1;
    while(q.size()) {
        int u = q.front();
        q.pop_front();
        inq[u] = 0;
        for(int i = head[u] ; ~i ; i = rest[i]) {
            int v = to[i];
            if(flow[i] && dis[v] > dis[u] + cost[i]) {
                dis[v] = dis[u] + cost[i];
                pre[v] = i;
                if(!inq[v]) {
                    if(q.size() && dis[v] < dis[q.front()]) q.push_front(v);
                    else q.push_back(v);
                    inq[v] = 1;
                }
            }
        }
    }
    return dis[t] != inf;
}

void sol() {
    while(spfa()) {
        int f = inf;
        for(int i = pre[t] ; ~i ; i = pre[from[i]]) f = min(f, flow[i]);
        for(int i = pre[t] ; ~i ; i = pre[from[i]]) flow[i] -= f, flow[i ^ 1] += f;
        ansf += f;
        ansc += f * dis[t];
    }
}

int p[1010][1010], w[1010][1010];

signed main() {
    memset(head, -1, sizeof(head));
    scanf("%lld%lld", &m, &n);
    
    s = N - 5, t = s + 1;
    
    for(int i = 1 ; i <= n ; ++ i) {
        int c; scanf("%lld", &c); insert(s, i, c, 0); 
    }
    for(int i = 1 ; i <= m ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            int c; scanf("%lld", &c); if(c) insert(j, n + i, inf, 0);
        }
    }
    for(int i = 1 ; i <= m ; ++ i) {
        int s; scanf("%lld", &s);
        for(int j = 1 ; j <= s ; ++ j) scanf("%lld", &p[i][j]); p[i][s + 1] = inf;
        for(int j = 1 ; j <= s + 1 ; ++ j) scanf("%lld", &w[i][j]);
        for(int j = 1 ; j <= s + 1 ; ++ j) insert(n + i, t, p[i][j] - p[i][j - 1], w[i][j]);
    }
    sol();
    printf("%lld\n", ansc);
}
