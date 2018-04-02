#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long ll;

const int N = 3010;

const int M = N * N;

int n, na, nb, m, a[N], b[N], c[N][N];

int head[N], rest[M], to[M], tot;

void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

int cnt(int x) {
    int res = 0;
    for( ; x ; x -= x & -x) ++ res;
    return res;
}

int mat[N], bel[N], vis[N], T, Q, ans, tag[N];

int get(int u) {
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(tag[v] == T && vis[v] != Q) {
            vis[v] = Q;
            if(bel[v] != Q || !mat[v] || get(mat[v])) {
                mat[v] = u;
                bel[v] = Q;
                return 1;
            }
        }
    }
    return 0;
}

int sol() {
    int res = 0;
    for(int i = 1 ; i <= nb ; ++ i) {
        if(tag[i] == T) {
            ++ Q;
            if(get(i)) ++ res;
        } else ++ res;
    }
    return nb - res;
}

int main() {
    scanf("%d%d%d", &na, &nb, &m);
    for(int i = 1 ; i <= na ; ++ i) scanf("%d", &a[i]);
    for(int i = 1 ; i <= nb ; ++ i) scanf("%d", &b[i]);
    for(int i = 1 ; i <= m ; ++ i) {
        int x, y; scanf("%d%d", &x, &y);
        c[x][y] = 1;
    }
    for(int i = 1 ; i <= nb ; ++ i) {
        if(b[i] & 1) {
            for(int j = 1 ; j <= nb ; ++ j) {
                if(!(b[j] & 1) && !(cnt(b[i] | b[j]) & 1)) {
                    add(i, j);
                }
            }
        }
    }
    ans = max(ans, sol());
    for(int i = 1 ; i <= na ; ++ i) {
        ++ T;
        for(int j = 1 ; j <= nb ; ++ j) {
            if(c[i][j]) {
                tag[j] = T;
            }
        }
        ans = max(ans, sol() + 1);
    }
    for(int i = 1 ; i <= na ; ++ i) {
        if(a[i] & 1) {
            for(int j = i + 1 ; j <= na ; ++ j) {
                if(!(a[j] & 1)) {
                    ++ T;
                    for(int k = 1 ; k <= nb ; ++ k) {
                        if(c[i][k] && c[j][k]) tag[k] = T;
                    }
                    ans = max(ans, sol() + 2);
                }
            }
        }
    }
    printf("%d\n", ans);
}

