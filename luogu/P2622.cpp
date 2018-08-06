// 隐式图最短路 状态压缩

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
#include <queue>

using namespace std;

int a[110][15], n, m;

vector<int> G[1 << 15];

const int INF = 0x3f3f3f3f;
queue<int> q;
int dis[1 << 15], inq[1 << 15];

void spfa(int s) {
    memset(dis, 0x3f, sizeof(dis));
    q.push(s);
    inq[s] = 1;
    dis[s] = 0;
    while(q.size()) {
        int u = q.front();
        q.pop();
        inq[u] = 0;
        for(int i = 0 ; i < G[u].size() ; ++ i) {
            int v = G[u][i];
            if(dis[v] > dis[u] + 1) {
                dis[v] = dis[u] + 1;
                if(!inq[v]) {
                    q.push(v);
                    inq[v] = 1;
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= m ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            scanf("%d", &a[i][j]);
        }
    }
    for(int s = 0 ; s < (1 << n) ; ++ s) {
        for(int i = 1 ; i <= m ; ++ i) {
            int ss = s;
            for(int j = 1 ; j <= n ; ++ j) {
                if(a[i][j] == 1) {
                    ss ^= (ss & (1 << (j - 1)));
                } else if(a[i][j] == -1) {
                    ss |= 1 << (j - 1);
                }
            }
            G[s].push_back(ss);
        }
    }
    spfa((1 << n) - 1);
    printf("%d\n", dis[0] < INF ? dis[0] : -1);
}
