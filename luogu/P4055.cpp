#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 110;

int n, m;
char str[N][N];

int id[N][N], id_cnt, col[N][N];

const int mv[4][2] = {
    { 0, 1 },
    { 1, 0 },
    { -1, 0 },
    { 0, -1 }
};

const int E = 1e6 + 10;
int head[E], rest[E], to[E], tot;
void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

int TIM, vis[E], ban[E], mat[E];

int dfs(int u) {
    if(ban[u]) return 0;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(vis[v] != TIM && !ban[v]) {
            vis[v] = TIM;
            if(!mat[v] || dfs(mat[v])) {
                mat[u] = v, mat[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

vector<pair<int, int> > ans;

int main() {
    scanf("%d%d", &n, &m);

    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%s", str[i] + 1);
        for(int j = 1 ; j <= m ; ++ j) {
            if(str[i][j] == '#') continue;
            id[i][j] = ++ id_cnt;
            col[i][j] = (i + j) & 1;
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            if(str[i][j] == '#') continue;
            if(col[i][j] == 1) {
                for(int k = 0 ; k < 4 ; ++ k) {
                    int x = i + mv[k][0], y = j + mv[k][1];
                    if(1 <= x && x <= n && 1 <= y && y <= m) {
                        if(str[x][y] == '#') continue;
                        add(id[i][j], id[x][y]);
                        add(id[x][y], id[i][j]);
                    }
                }
            }
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            if(str[i][j] == '#') continue;
            if(!mat[id[i][j]]) {
                ++ TIM;
                dfs(id[i][j]);
            }
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            if(str[i][j] == '#') continue;
            int u = id[i][j];
            if(!mat[u]) {
                ans.push_back(make_pair(i, j));
            } else {
                int v = mat[u];
                ban[u] = 1, mat[u] = mat[v] = 0, ++ TIM;
                if(dfs(v)) {
                    ans.push_back(make_pair(i, j));
                } else {
                    mat[u] = v, mat[v] = u;
                }
                ban[u] = 0;
            }
        }
    }
    puts(ans.size() ? "WIN" : "LOSE");
    sort(ans.begin(), ans.end());
    for(int i = 0 ; i < ans.size() ; ++ i) {
        printf("%d %d\n", ans[i].first, ans[i].second);
    }
}
