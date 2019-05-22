#include "bits/stdc++.h"
#include <random>
using namespace std;

const int N = 20;

int n, m, k, A[N][N], M[N][N];

int ids[N][N], tot, tmp[N * N], col[N * N], val[N * N];
vector<int> g[N * N];
int inq[N * N]; queue<int> que;

const int inf = 0x3f3f3f3f;
int f[1 << 8][N * N], ans;

void spfa(int *f) {
    while(que.size()) {
        int u = que.front(); que.pop();
        inq[u] = 0;
        for(int v: g[u]) {
            if(f[v] > f[u] + val[v]) {
                f[v] = f[u] + val[v];
                if(!inq[v]) {
                    que.push(v);
                    inq[v] = 1;
                }
            }
        }
    }
}

void runprog() {

    // for(int i = 1 ; i <= tot ; ++ i) {
    //     printf("%d ", col[i]);
    // } puts("");

    for(int i = 1 ; i <= tot ; ++ i) {
        for(int s = 0 ; s < (1 << (k + 1)) ; ++ s) {
            f[s][i] = inf;
        }
        f[1 << col[i]][i] = val[i];
    }
    for(int s = 0 ; s < (1 << (k + 1)) ; ++ s) {

        for(int i = 1 ; i <= tot ; ++ i) {
            for(int t = (s - 1) & s ; t ; t = (t - 1) & s) {
                if(f[t][i] != inf && f[s - t][i] != inf) {
                    // printf("%d %d %d\n", f[s][i], f[t][i], f[s - t][i]);
                    f[s][i] = min(f[s][i], f[t][i] + f[s - t][i] - val[i]);
                }
            }
            if(f[s][i] != inf) {
                que.push(i);
                inq[i] = 1;
            }
        }
        spfa(f[s]);
        if(__builtin_popcount(s - (s & 1)) == k) {
            for(int i = 1 ; i <= tot ; ++ i) {
                ans = min(ans, f[s][i]);
                // printf("f[%d][%d] = %d\n", s, i, f[s][i]);
            }
        }
    }
}

int main() {

    mt19937 mt_rand(time(0));
    // cout << mt_rand() << endl;

    scanf("%d%d%d", &n, &m, &k);
    int cnt = 0;
    map<int, int> num, bak;
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            scanf("%d", &A[i][j]);
            if(A[i][j] != -1) {
                ids[i][j] = ++ tot;
                if(num[A[i][j]]) {
                    A[i][j] = num[A[i][j]];
                } else {
                    bak[++ cnt] = A[i][j];
                    A[i][j] = num[A[i][j]] = cnt;
                    
                }
            }
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            scanf("%d", &M[i][j]);
            if(ids[i][j]) {
                val[ids[i][j]] = M[i][j];
            }
            if(A[i][j] == -1) {
                continue;
            }
            int mv[4][2] = {
                { 0, 1 },
                { 1, 0 },
                { -1, 0 },
                { 0, -1 }
            };
            for(int k = 0 ; k < 4 ; ++ k) {
                int x = i + mv[k][0], y = j + mv[k][1];
                if(ids[x][y]) {
                    g[ids[i][j]].push_back(ids[x][y]);
                }
            }
        }
    }

    // for(int i = 1 ; i <= n ; ++ i) {
    //     for(int j = 1 ; j <= m ; ++ j) {
    //         printf("%d ", A[i][j]);
    //     } puts("");
    // } puts("");

    // for(int i = 1 ; i <= n ; ++ i) {
    //     for(int j = 1 ; j <= m ; ++ j) {
    //         printf("%d ", M[i][j]);
    //     } puts("");
    // } puts("");

    tmp[num[0]] = 0;
    ans = inf;
    for(int T = 1 ; T <= 200 ; ++ T) {
        for(int i = 1 ; i <= cnt ; ++ i) {
            if(bak[i] != 0) {
                tmp[i] = mt_rand() % k + 1;
            }
        }
        // for(int i = 1 ; i <= cnt ; ++ i) {
        //     printf("%d -> %d\n", bak[i], tmp[i]);
        // }
        for(int i = 1 ; i <= n ; ++ i) {
            for(int j = 1 ; j <= m ; ++ j) {
                if(ids[i][j]) {
                    col[ids[i][j]] = tmp[A[i][j]];
                }
            }
        }
        runprog();
    }
    printf("%d\n", ans == inf ? -1 : ans);
}
