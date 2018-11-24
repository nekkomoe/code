#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6, M = N; const double eps = 1e-6;

double mxf;

int head[N], rest[M], to[M], tot = 1, P, n, m;

double w[M]; int wmet[M];

void sig(int u, int v, int w) {
    to[++ tot] = v, :: w[tot] = wmet[tot] = w, rest[tot] = head[u], head[u] = tot;
}
void add(int u, int v, int w) {
    sig(u, v, w), sig(v, u, 0);
}

int dis[N];

int bfs() {
    queue<int> q;
    for(int i = 1 ; i <= n ; ++ i) dis[i] = -1;
    dis[1] = 1, q.push(1);
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(w[i] > eps && dis[v] == -1) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    return dis[n] != -1;
}

double dfs(int u, double f) {
    double use = 0;
    if(u == n || fabs(f) < eps) return f;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(fabs(w[i]) > eps && dis[v] == dis[u] + 1) {
            double a = dfs(v, min(f - use, w[i]));
            w[i] -= a, w[i ^ 1] += a, use += a;
            if(fabs(use - f) < eps) break;
        }
    }
    if(fabs(use) < eps) dis[u] = -1;
    return use;
}
double get(double T) {
    for(int i = 2 ; i <= tot ; ++ i) {
        w[i] = min((double) wmet[i], T);
    }
    double res = 0;
    while(bfs()) {
        res += dfs(1, 1e9);
    }
    return res;
}

int main() {
    scanf("%d%d%d", &n, &m, &P);
    for(int i = 1, u, v, w ; i <= m ; ++ i) {
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
    }
    mxf = get(50000);
    double l = 0, r = min(50000.0, mxf);
    for(int i = 1 ; i <= 100 ; ++ i) {
        double mid = (l + r) / 2;
        if(fabs(mxf - get(mid)) < eps) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << fixed << setprecision(0) << mxf << endl;
    cout << fixed << setprecision(3) << l * P << endl;
}

