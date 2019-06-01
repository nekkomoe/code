#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
using namespace std;
const double eps = 1e-8, inf = 1e9;
int n, m, type, id[3010], tp[3010];
double a[3010 * (1 + 2)][3010];
void pivot(int r, int c) {
    swap(id[r + n], id[c]);
    double t = -a[r][c];
    a[r][c] = -1;
    FOR(i, 0, n) a[r][i] /= t;
    FOR(i, 0, m) if (a[i][c] && r != i) {
        t = a[i][c];
        a[i][c] = 0;
        FOR(j, 0, n) a[i][j] += t * a[r][j];
    } 
}
void solve() {
    double t;
    FOR(i, 1, n) id[i] = i;
    while (1) {
        int i = 0, j = 0; double _w = -eps;
        FOR(k, 1, m) if (a[k][0] < _w) _w = a[i = k][0];
        if (!i) break;
        FOR(k, 1, n) if (a[i][k] > eps) {j = k; break;}
        if (!j) return puts("-1"), void();
        pivot(i, j);
    }
    while (1) {
        int i = 0, j = 0; double _w = eps;
        FOR(k, 1, n) if (a[0][k] > _w) _w = a[0][j = k];
        if (!j) break;
        _w = inf;
        FOR(k, 1, m) if (a[k][j] < -eps && (t = -a[k][0] / a[k][j]) < _w) _w = t, i = k;
        if (!i) return puts("-1"), void();
        pivot(i, j);
    }
    // printf("%.9f\n", a[0][0]);
    printf("%.0f\n", a[0][0]);
    FOR(i, n + 1, n + m) tp[id[i]] = i - n;
    // if (type)
    //     FOR(i, 1, n) printf("%.9f ", tp[i] ? a[tp[i]][0] : 0);
}




const int N = 510;
int x, y;
vector<int> g_red[N], g_blue[N];
int q_red, q_blue;
int tag_red[N], tag_blue[N];
int w[N];


namespace runthefafamain {
    const int N = 510;
    
    vector<int> son_red[N], son_blue[N];

    void dfs_red(int u, int fa) {
        son_red[u].emplace_back(u);
        for(int v: g_red[u]) {
            if(v != fa) {
                dfs_red(v, u);
                for(int t: son_red[v]) {
                    son_red[u].emplace_back(t);
                }
            }
        }
    }

    void dfs_blue(int u, int fa) {
        son_blue[u].emplace_back(u);
        for(int v: g_blue[u]) {
            if(v != fa) {
                dfs_blue(v, u);
                for(int t: son_blue[v]) {
                    son_blue[u].emplace_back(t);
                }
            }
        }
    }

    void runprog() {
        memset(tag_red, -1, sizeof tag_red);
        memset(tag_blue, -1, sizeof tag_blue);

        scanf("%d%d%d", &n, &x, &y);
        for(int i = 1 ; i <= n ; ++ i) {
            scanf("%d", &w[i]);
        }
        for(int i = 1, u, v ; i < n ; ++ i) {
            scanf("%d%d", &u, &v);
            g_red[u].push_back(v);
            g_red[v].push_back(u);
        }
        for(int i = 1, u, v ; i < n ; ++ i) {
            scanf("%d%d", &u, &v);
            g_blue[u].push_back(v);
            g_blue[v].push_back(u);
        }
        scanf("%d", &q_red);
        for(int i = 1, a, b ; i <= q_red ; ++ i) {
            scanf("%d%d", &a, &b);
            tag_red[a] = b;
        }
        scanf("%d", &q_blue);
        for(int i = 1, a, b ; i <= q_blue ; ++ i) {
            scanf("%d%d", &a, &b);
            tag_blue[a] = b;
        }

        dfs_red(x, 0);
        dfs_blue(y, 0);

        for(int i = 1 ; i <= n ; ++ i) {
            a[0][i] = w[i];
        }

        m = 0;
        // m = n + 2 * (q_red + q_blue)

        for(int i = 1 ; i <= n ; ++ i) {
            ++ m;
            a[m][i] = -1;
            a[m][0] = 1;
        }

        // red
        for(int i = 1 ; i <= n ; ++ i) {
            if(tag_red[i] != -1) {

                // for(int j: son_red[i]) {
                //     printf("%d + ", j);
                // }
                // printf(" = %d\n", tag_red[i]);

                ++ m;
                for(int j: son_red[i]) {
                    // sum >= tag_red

                    // -sum <= -tag_red
                    a[m][j] = 1;
                }
                a[m][0] = -tag_red[i];

                ++ m;
                for(int j: son_red[i]) {
                    // sum <= tag_red

                    a[m][j] = -1;
                }
                a[m][0] = tag_red[i];
            }
        }

        // blue
        for(int i = 1 ; i <= n ; ++ i) {
            if(tag_blue[i] != -1) {

                // for(int j: son_blue[i]) {
                //     printf("%d + ", j);
                // }
                // printf(" = %d\n", tag_blue[i]);

                ++ m;
                for(int j: son_blue[i]) {
                    // sum >= tag_blue

                    // -sum <= -tag_blue
                    a[m][j] = 1;
                }
                a[m][0] = -tag_blue[i];

                ++ m;
                for(int j: son_blue[i]) {
                    // sum <= tag_blue

                    a[m][j] = -1;
                }
                a[m][0] = tag_blue[i];
            }
        }
        solve();
    }
}


int main() {
    runthefafamain :: runprog();
}
