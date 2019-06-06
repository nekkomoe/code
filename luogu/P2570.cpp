#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e6 + 10;
const double eps = 1e-6;

int head[N], rest[N], to[N], tot;
double flow[N];

int s, t, cnt, dis[N];

void add_s(int u, int v, double f) {
    to[++ tot] = v, flow[tot] = f, rest[tot] = head[u], head[u] = tot;
}
void add(int u, int v, double f) {
    add_s(u, v, f), add_s(v, u, 0);
}

int bfs() {
    queue<int> q;
    for(int i = 1 ; i <= cnt ; ++ i) {
        dis[i] = -1;
    }
    dis[s] = 1, q.push(s);
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(dis[v] == -1 && fabs(flow[i]) > eps) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    return dis[t] != -1;
}
double dfs(int u, double f) {
    if(u == t) {
        return f;
    }
    double use = 0;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(dis[v] == dis[u] + 1 && fabs(flow[i]) > eps) {
            double a = dfs(v, min(f - use, flow[i]));
            flow[i] -= a, flow[i ^ 1] += a, use += a;
            if(fabs(use - f) < eps) {
                break;
            }
        }
    }
    if(fabs(f) < eps) {
        dis[u] = -1;
    }
    return use;
}

void clsall() {
    tot = 1;
    for(int i = 1 ; i <= cnt ; ++ i) {
        head[i] = 0;
    }
    cnt = 0;
}

namespace TT {
int n, m;
int p[N], r[N], d[N];
int s[N], sum;
double getmxflow() {
    double res = 0;
    while(bfs()) {
        res += dfs(:: s, 1e15);
    }
    return res;
}

int check(double T) {
    clsall();
    vector<double> num;
    for(int i = 1 ; i <= n ; ++ i) {
        num.emplace_back(r[i]);
        num.emplace_back(d[i] + T);
    }
    sort(num.begin(), num.end());
    num.erase(unique(num.begin(), num.end()), num.end());
    cnt = 5000, :: s = cnt, :: t = :: s - 1;

    for(int i = 1 ; i <= n ; ++ i) {
        add(:: s, i, p[i]);
    }
    for(int i = 1 ; i < num.size() ; ++ i) {
        double delta = num[i] - num[i - 1];
        int ids = n + (i - 1) * m;
        for(int j = 1 ; j <= m ; ++ j) {
            add(ids + j, t, j * delta * s[j]);
        }
        for(int j = 1 ; j <= n ; ++ j) {
            if(r[j] <= num[i - 1] && num[i] <= d[j] + T) {
                for(int k = 1 ; k <= m ; ++ k) {
                    add(j, ids + k, delta * s[k]);
                }
            }
        }
    }
    return fabs(getmxflow() - sum) < eps;
}

void runprog() {
    sum = 0;
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d%d%d", &p[i], &r[i], &d[i]);
        sum += p[i];
    }
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%d", &s[i]);
    }
    int ttt = s[1];
    s[m + 1] = 0;
    sort(s + 1, s + 1 + m, greater<int> ());
    for(int i = 1 ; i <= m ; ++ i) {
        s[i] -= s[i + 1];
    }
    double l = 0, r = 1.0 * sum / ttt;
    for(int i = 1 ; i <= 30 ; ++ i) {
        double mid = (l + r) / 2;
        if(check(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    printf("%.5lf\n", l);
}
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        TT :: runprog();
    }
}
