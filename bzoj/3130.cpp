#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n, m, s, t;

queue<int> q;

int head[N], rest[N], to[N], tot, dis[N];

double flow[N];

const double eps = 1e-6;

void add_sub(int u, int v, double f) {
    to[tot] = v;
    flow[tot] = f;
    rest[tot] = head[u];
    head[u] = tot ++;
}

void add(int u, int v, double f) {
    add_sub(u, v, f);
    add_sub(v, u, 0);
}

bool bfs() {
    memset(dis, -1, sizeof dis);
    q.push(s);
    dis[s] = 0;
    while(q.size()) {
        int u = q.front();
        q.pop();
        for(int i = head[u] ; ~i ; i = rest[i]) {
            int v = to[i];
            if(flow[i] > eps && dis[v] == -1) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    return dis[t] != -1;
}

double dfs(int u, double fw) {
    if(u == t || fabs(fw) < eps) return fw;
    double use = 0;
    for(int i = head[u] ; ~i ; i = rest[i]) {
        int v = to[i];
        if(flow[i] > eps && dis[v] == dis[u] + 1) {
            double a = dfs(v, min(flow[i], fw - use));
            flow[i] -= a;
            flow[i ^ 1] += a;
            use += a;
            if(fabs(use - fw) < eps) break;
        }
    }
    if(fabs(use) < eps) dis[u] = -1;
    return use;
}

double sol() {
    double ret = 0;
    while(bfs()) ret += dfs(s, 1e9);
    return ret;
}

int p;

struct E {
    int u, v, f;
} e[N];

double ans;

int check(double mid) {
    
    memset(head, -1, sizeof head);
    
    tot = 0;
    
    for(int i = 1 ; i <= m ; ++ i) {
        add(e[i].u, e[i].v, min((double) e[i].f, mid));
    }
    return fabs(sol() - ans) < eps;
}

int main() {
    
    memset(head, -1, sizeof head);
    
    double l = 0, r = 0;
    
    scanf("%d%d%d", &n, &m, &p), s = 1, t = n;
    for(int i = 1 ; i <= m ; ++ i) {
        int u, v, f; scanf("%d%d%d", &u, &v, &f);
        add(u, v, f);
        e[i] = (E) {u, v, f};
        r = max(r, (double) f);
    }
    ans = sol();
    printf("%d\n", (int) ans);
    
    
    for(int i = 1 ; i <= 50 ; ++ i) {
        double mid = (l + r) / 2;
        if(check(mid)) r = mid;
        else l = mid;
    }
    
    printf("%.3lf\n", l * p);
    
}
