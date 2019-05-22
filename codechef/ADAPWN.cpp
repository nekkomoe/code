#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 2e5 + 10;
const int inf = 20000;

int head[N], rest[N], to[N], w[N], tot, cur[N];
inline void add_sig(int u, int v, int _w) {
    to[++ tot] = v, w[tot] = _w, rest[tot] = head[u], head[u] = tot;
}
inline void add(int u, int v, int _w) {
    add_sig(u, v, _w);
    add_sig(v, u, 0);
}

int n; char str[110][110];

int cnt;

inline void clear() {
    for(int i = 0 ; i <= cnt ; ++ i) {
        head[i] = 0;
    }
    tot = 1;
    cnt = 0;
}

int dis[N], s, t;
inline int bfs() {
    for(int i = 1 ; i <= cnt ; ++ i) {
        dis[i] = -1;
    }
    queue<int> q;
    q.push(s), dis[s] = 1;
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(w[i] && dis[v] == -1) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    return dis[t] != -1;
}

inline int dfs(int u, int f) {
    if(u == t || !f) {
        return f;
    }
    int use = 0;
    for(int &i = cur[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(w[i] && dis[v] == dis[u] + 1) {
            int a = dfs(v, min(f - use, w[i]));
            w[i] -= a, w[i ^ 1] += a, use += a;
            if(use == f) {
                break;
            }
        }
    }
    if(!use) {
        dis[u] = -1;
    }
    return use;
}

inline int getmxflow() {
    int res = 0;
    while(bfs()) {
        for(int i = 1 ; i <= cnt ; ++ i) {
            cur[i] = head[i];
        }
        res += dfs(s, inf);
    }
    return res;
}

int ids[110][110];

int ban[110][110];
int vis[110 * 110];

const int mv[2][2] = {
    { -1, -1 },
    { -1, 1 }
};

int que[N], l, r;

void runprog() {

    clear();

    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%s", str[i] + 1);
    }

    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            if(str[i][j] == 'O') {
                ids[i][j] = ++ cnt;
                ban[i][j] = 0;
            }
        }
    }

    s = ++ cnt, t = ++ cnt;

    for(int i = 1 ; i <= cnt ; ++ i) {
        vis[i] = 0;
    }

    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            if(str[i][j] == 'O') {
                if(str[i - 1][j - 1] == 'O' || str[i - 1][j + 1] == 'O') {
                    if(i & 1) {
                        add(s, ids[i][j], 1);
                    } else {
                        add(ids[i][j], t, 1);
                    }
                } else {
                    if(i & 1) {
                        add(s, ids[i][j], inf);
                    } else {
                        add(ids[i][j], t, inf);
                    }
                }
                for(int k = 0 ; k < 2 ; ++ k) {
                    int x = i + mv[k][0], y = j + mv[k][1];
                    if(1 <= x && x <= n && 1 <= y && y <= n && str[x][y] == 'O') {
                        if(i % 2 == 1) {
                            add(ids[i][j], ids[x][y], inf);
                        } else {
                            add(ids[x][y], ids[i][j], inf);
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", getmxflow());
    
    // queue<int> q;
    // q.push(s);
    // while(q.size()) {
    //     int u = q.front(); q.pop();
    //     vis[u] = 1;
    //     for(int i = head[u] ; i ; i = rest[i]) {
    //         int v = to[i];
    //         if(w[i] && !vis[v]) {
    //             q.push(v);
    //         }
    //     }
    // }
    l = 1, r = 0;
    que[++ r] = s, vis[s] = 1;
    while(l <= r) {
        int u = que[l ++];
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(w[i] && !vis[v]) {
                vis[v] = 1;
                que[++ r] = v;
            }
        }
    }

    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            if(str[i][j] == 'O') {
                if(vis[ids[i][j]] == 1) {
                    // 属于 S
                    if(i % 2 == 0) {
                        ban[i][j] = 1;
                    }
                } else {
                    // 属于 T
                    if(i % 2 == 1) {
                        ban[i][j] = 1;
                    }
                }
            }
        }
    }

    for(int i = n ; i >= 1 ; -- i) {
        for(int j = 1 ; j <= n ; ++ j) {
            if(str[i][j] == 'O' && ban[i][j]) {
                for(int k = 0 ; k < 2 ; ++ k) {
                    int x = i + mv[k][0], y = j + mv[k][1];
                    if(1 <= x && x <= n && 1 <= y && y <= n && str[x][y] == 'O') {
                        str[i][j] = '.';
                        printf("%d %d %c\n", i, j, k == 0 ? 'L' : 'R');
                        break;
                    }
                }
            }
        }
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
