#include <bits/stdc++.h>
using namespace std;
const int N = 12, inf = 0x3f3f3f3f;
int n, m, val[N][N], id[N][N], tot, cnt, rev[N * N];
char output[N][N];

int to(int x) {
    return 1 << (x - 1);
}

int f[1 << 11][N * N], newval[N * N];

queue<int> q; int inq[N * N];

pair<pair<int, int>, pair<int, int> > from[1 << 11][N * N];

int tra[N * N][4]; 

void spfa(int *f, int s) {
    while(q.size()) {
        int u = q.front(); q.pop(); inq[u] = 0;
        for(int i = 0 ; i < 4 ; ++ i) {
            int v = tra[u][i];
            if(!v) break;
            if(f[v] > f[u] + newval[v]) {
                f[v] = f[u] + newval[v];
                from[s][v] = make_pair(make_pair(s, u), make_pair(-1, -1));
                if(!inq[v]) {
                    q.push(v);
                    inq[v] = 1; 
                }
            }
        }
    }
} 

int mv[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };

pair<int, int> la[N * N];

void dfs(int s, int i) {
    if(i <= 0) return ;
    output[la[i].first][la[i].second] = 'o';
    dfs(from[s][i].first.first, from[s][i].first.second);
    dfs(from[s][i].second.first, from[s][i].second.second);
}

int main() {
    memset(f, 0x3f, sizeof f);
    scanf("%d%d", &n, &m);
    
    for(int i = 1 ; i <= n ; ++ i)
        for(int j = 1 ; j <= m ; ++ j) {
            scanf("%d", &val[i][j]);
            newval[id[i][j] = ++ tot] = val[i][j];
            output[i][j] = '_';
            la[tot] = make_pair(i, j);
        }
    
    for(int i = 1 ; i <= n ; ++ i)
        for(int j = 1 ; j <= m ; ++ j) {
            if(!val[i][j]) {
                f[rev[id[i][j]] = to(++ cnt)][id[i][j]] = 0;
            }
            for(int k = 0, fafa = 0 ; k < 4 ; ++ k) {
                int x = i + mv[k][0], y = j + mv[k][1];
                if(1 <= x && x <= n && 1 <= y && y <= m) {
                    tra[id[i][j]][fafa ++] = id[x][y];
                }
            }
        }
    
    int all = to(cnt + 1) - 1;
    for(int s = 0 ; s <= all ; ++ s) {
        for(int i = 1 ; i <= tot ; ++ i) {
            for(int t = (s - 1) & s ; t ; t = (t - 1) & s) {
                if(f[s - t][i] + f[t][i] - newval[i] < f[s][i]) {
                    f[s][i] = f[s - t][i] + f[t][i] - newval[i];
                    from[s][i] = make_pair(make_pair(s - t, i), make_pair(t, i));
                }
                f[s][i] = min(f[s][i], f[s - t][i] + f[t][i] - newval[i]);
            }
            if(f[s][i] != inf) {
                q.push(i); inq[i] = 1;
            }
        }
        spfa(f[s], s);
    }
    
    int ans = inf;
    for(int i = 1 ; i <= tot ; ++ i)
        ans = min(ans, f[all][i]);
    printf("%d\n", ans);
    
    for(int i = 1 ; i <= tot ; ++ i) {
        if(f[all][i] == ans) {
            dfs(all, i);
            break;
        }
    }
    
    for(int i = 1 ; i <= n ; ++ i)
        for(int j = 1 ; j <= m ; ++ j)
            if(val[i][j] == 0)
                output[i][j] = 'x';
    
    for(int i = 1 ; i <= n ; ++ i)
        puts(output[i] + 1);
}
