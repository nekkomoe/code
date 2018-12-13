#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//#define double long double

const int N = 200 + 10, M = 1e6 + 10;

int n, a[N][N], b[N][N];
int head[N], rest[M], from[M], to[M], flow[M], tot, S, T;
double cost[M];

const int inf = 1e9;

void sig(int u, int v, int f, double c) {
    from[++ tot] = u, to[tot] = v, flow[tot] = f, cost[tot] = c, rest[tot] = head[u], head[u] = tot;
}

void add(int u, int v, int f, double c) {
    
//    printf("%d -> %d, flow = %d, cost = %.2f\n", u, v, f, c);
    
    sig(u, v, f, c), sig(v, u, 0, -c);
}

double dis[N]; int inq[N], pre[N];
int spfa() {
    for(int i = 1 ; i <= T ; ++ i) dis[i] = -inf, pre[i] = 0;
    queue<int> q; q.push(S); dis[S] = 0; inq[S] = 1;
    while(q.size()) {
        int u = q.front(); q.pop(); inq[u] = 0;
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(flow[i] && dis[v] < dis[u] + cost[i]) {
                dis[v] = dis[u] + cost[i];
                pre[v] = i;
                if(!inq[v]) q.push(v), inq[v] = 1;
            }
        }
    }
    return dis[T] > -inf;
}

int check(double mid) {
    
//    printf("fck: mid = %.2f\n", mid);
    
    tot = 1;
    S = 2 * n + 1, T = 2 * n + 2;

    for(int i = 1 ; i <= T ; ++ i) head[i] = 0;
    
    for(int i = 1 ; i <= n ; ++ i) {
        add(S, i, 1, 0);
        for(int j = 1 ; j <= n ; ++ j) {
            add(i, j + n, 1, a[i][j] - b[i][j] * mid);
            
//            printf("%d, %d, %.2f, poi = %.2f -> %.2f\n", a[i][j], b[i][j], mid, b[i][j] * mid, a[i][j] - b[i][j] * mid);
        }
        add(i + n, T, 1, 0);
    }
    
    double res = 0;
    while(spfa()) {
        int mn = inf;
        for(int i = pre[T] ; i ; i = pre[from[i]]) mn = min(mn, flow[i]);
        for(int i = pre[T] ; i ; i = pre[from[i]]) flow[i] -= mn, flow[i ^ 1] += mn;
        res += mn * dis[T];
    }
    
//    cout << "res = " << fiexd << setprecision(2) << res << endl;
    
    return res <= 0;
}

int main() {
//    freopen("data.in", "r", stdin);
    
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i)
        for(int j = 1 ; j <= n ; ++ j)
            scanf("%d", &a[i][j]);
    for(int i = 1 ; i <= n ; ++ i)
        for(int j = 1 ; j <= n ; ++ j)
            scanf("%d", &b[i][j]);
    double l = 0, r = 1e4, ans = 0;
    
//    cout << check(5.357143) << endl;
//    exit(0);
    
    for(int i = 1 ; i <= 50 ; ++ i) {
        double mid = (l + r) / 2;
        if(check(mid)) {
            ans = mid;
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << fixed << setprecision(6) << ans << endl;
} 

