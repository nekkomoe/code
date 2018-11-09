#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10, inf = 0x3f3f3f3f;
struct E { int v, w; };
vector<E> g[N];
int n, m, d, rev[N];
int to(int x) { return 1 << (x - 1); }
int f[1 << 11][N], inq[N];
 
queue<int> q;
void spfa(int *f) {
    while(q.size()) {
        int u = q.front(); q.pop();
        inq[u] = 0; 
        for(int i = 0 ; i < g[u].size() ; ++ i) {
            int v = g[u][i].v, w = g[u][i].w;
            if(f[v] > f[u] + w) {
                f[v] = f[u] + w;
                if(!inq[v]) {
                    q.push(v);
                    inq[v] = 1;
                }
            }
        }
    }
}
int h[1 << 11];
vector<int> C[12];
int pindao[12], bianhao[12];
bool check(int s) {
    for(int i = 1 ; i <= 10 ; ++ i) {
        for(int j = 0 ; j < C[i].size() ; ++ j) {
            if(!(s & rev[C[i][j]]) != !(s & rev[C[i][0]])) {
                return 0;
            }
        }
    }
    return 1;
}
 
 
int main() {
//    freopen("data.in", "r", stdin); 
    cin >> n >> m >> d;
    for(int i = 1, u, v, w ; i <= m ; ++ i) {
        cin >> u >> v >> w;
        g[u].push_back((E) { v, w });
        g[v].push_back((E) { u, w });
    }
    memset(f, 0x3f, sizeof f);
    memset(h, 0x3f, sizeof h);
    int all = to(d + 1) - 1;
     
    int cnt = 0;
    for(int i = 1 ; i <= d ; ++ i) {
        cin >> pindao[i] >> bianhao[i];
        C[pindao[i]].push_back(bianhao[i]);
        f[rev[bianhao[i]] = to(++ cnt)][bianhao[i]] = 0;
    }
    for(int s = 0 ; s <= all ; ++ s) {
        for(int i = 1 ; i <= n ; ++ i) {
            for(int t = (s - 1) & s ; t ; t = (t - 1) & s) {
                f[s][i] = min(f[s][i], f[t][i] + f[s - t][i]);
            }
            if(f[s][i] != inf) {
                q.push(i);
                inq[i] = 1;
            }
        }
        spfa(f[s]);
        for(int i = 1 ; i <= n ; ++ i)
            h[s] = min(h[s], f[s][i]); 
    }
    for(int s = 0 ; s <= all ; ++ s)
        for(int t = (s - 1) & s ; t ; t = (t - 1) & s)
            if(check(t) && check(s - t))
                h[s] = min(h[s], h[t] + h[s - t]);
    int ans = h[all];
    printf("%d\n", ans == inf ? -1 : ans);
}
