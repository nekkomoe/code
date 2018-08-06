#include "bits/stdc++.h"
using namespace std;
const int N = 3010;
int dis[N][N];
int head[N], rest[2 * N], to[2 * N], tot, n, m;
int inq[N], s1, t1, l1, s2, t2, l2;

void add(int u, int v) { to[++ tot] = v, rest[tot] = head[u], head[u] = tot; }
void spfa(int s) {
    memset(dis[s], 0x3f, sizeof dis[s]);
    dis[s][s] = 0;
    queue<int> q;
    q.push(s), inq[s] = 1;
    while(q.size()) {
        int u = q.front(); q.pop(); inq[u] = 0;
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(dis[s][v] > dis[s][u] + 1) {
                dis[s][v] = dis[s][u] + 1;
                if(!inq[v]) q.push(v), inq[v] = 1;
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, u, v ; i <= m ; ++ i) scanf("%d%d", &u, &v), add(u, v), add(v, u);
    scanf("%d%d%d", &s1, &t1, &l1);
    scanf("%d%d%d", &s2, &t2, &l2);
    for(int i = 1 ; i <= n ; ++ i) spfa(i);
    if(dis[s1][t1] > l1 || dis[s2][t2] > l2) return puts("-1"), 0;
    int ans = dis[s1][t1] + dis[s2][t2];
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            if(dis[s1][i] + dis[i][j] + dis[j][t1] <= l1 && dis[s2][i] + dis[i][j] + dis[j][t2] <= l2)
                ans = min(ans, dis[s1][i] + dis[i][j] + dis[j][t1] + dis[s2][i] + dis[j][t2]);
            if(dis[t1][i] + dis[i][j] + dis[j][s1] <= l1 && dis[s2][i] + dis[i][j] + dis[j][t2] <= l2)
                ans = min(ans, dis[t1][i] + dis[i][j] + dis[j][s1] + dis[s2][i] + dis[j][t2]);
            if(dis[s1][i] + dis[i][j] + dis[j][t1] <= l1 && dis[t2][i] + dis[i][j] + dis[j][s2] <= l2)
                ans = min(ans, dis[s1][i] + dis[i][j] + dis[j][t1] + dis[t2][i] + dis[j][s2]);
            if(dis[t1][i] + dis[i][j] + dis[j][s1] <= l1 && dis[t2][i] + dis[i][j] + dis[j][s2] <= l2)
                ans = min(ans, dis[t1][i] + dis[i][j] + dis[j][s1] + dis[t2][i] + dis[j][s2]);
        }
    }
    printf("%d\n", m - ans);
}
