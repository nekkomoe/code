#include "bits/stdc++.h"
using namespace std;

const int N = 1e5 + 10, inf = 0x3f3f3f3f;

int min_edge[300][300], min_set[300 * 300], mod, mst[300 * 300], n, m, neko[N];

int get_cost(int x, int y) {
    int res = inf;
    for(int i = 0 ; i < 8 ; ++ i) {
        for(int j = 0 ; j < 8 ; ++ j) {
            if(x & (1 << i)) {
                if(y & (1 << j)) {
                    res = min(res, i ^ j);
                }
            }
        }
    }
    return res;
}

struct T {
    int s, ans, lc, rc;
} c[N << 5];
int f[N][30], tot;

void build(int len) {
    for(int i = 0 ; i < len ; ++ i) {
        if(neko[i]) {
            f[i][0] = ++ tot;
            c[tot] = (T) { 1, -1, 0, 0 };
        }
    }
    for(int j = 1, k = 1 ; k < len ; ++ j, k <<= 1) {
        for(int i = 0 ; i + k < len ; ++ i) {
            int lc = f[i][j - 1], rc = f[i + k][j - 1];
            if(lc || rc) {
                f[i][j] = ++ tot;
                c[tot] = (T) { (c[lc].s | (c[rc].s << k)), -1, lc, rc };
            }
        }
    }
}

int get_min_edge(int x, int y, int len) {
    if(!x || !y) return inf;
    if(len == 8) return min_edge[c[x].s][c[y].s];
    int son_len = len >> 1;
    int res = min(get_min_edge(c[x].lc, c[y].lc, son_len), get_min_edge(c[x].rc, c[y].rc, son_len));
    if(res != inf) return res;
    return min(get_min_edge(c[x].lc, c[y].rc, son_len), get_min_edge(c[x].rc, c[y].lc, son_len)) + son_len;
}

int run_mst(int u, int len) {
    if(c[u].ans !=- 1) return c[u].ans;
    if(len <= 16) return c[u].ans = mst[c[u].s];
    int son_len = len >> 1;
    if(!c[u].lc) return c[u].ans = run_mst(c[u].rc, son_len);
    if(!c[u].rc) return c[u].ans = run_mst(c[u].lc, son_len);
    c[u].ans = run_mst(c[u].lc, son_len) + run_mst(c[u].rc, son_len);
    c[u].ans += get_min_edge(c[u].lc, c[u].rc, son_len) + son_len;
    return c[u].ans;
}

int dis[N];
int get_mst(int x){
    for(int i = 0 ; i < 16 ; ++ i) dis[i] = inf;
    for(int i = 0 ; i < 16 ; ++ i) {
        if(x & (1 << i)) {
            dis[i] = 0;
            break;
        }
    }
    int res = 0;
    while(x) {
        int mn = inf, pos = 0;
        for(int i = 0 ; i < 16 ; ++ i) {
            if((x & (1 << i)) && mn > dis[i]) {
                pos = i;
                mn = dis[i];
            }
        }
        res += mn, x -= 1 << pos;
        for(int i = 0 ; i < 16 ; ++ i) {
            if((x & (1 << i))) {
                dis[i] = min(dis[i], pos ^ i);
            }
        }
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &m), mod = 1 << m;
    for(int i = 1, x ; i <= n ; ++ i) {
        scanf("%d", &x);
        neko[x] = neko[x + mod] = 1;
    }
    for(int i = 1 ; i < 256 ; ++ i) {
        for(int j = 1 ; j < 256 ; ++ j) {
            min_edge[i][j] = get_cost(i, j);
        }
    }
    for(int i = 1 ; i < 65536 ; ++ i) {
        mst[i] = get_mst(i);
    }
    build(mod << 1);
    int q; scanf("%d", &q);
    int delta = 0;
    while(q --) {
        int newd;scanf("%d", &newd);
        delta = ((delta - newd) % mod + mod) % mod;
        // printf("%d\n", mod <= 16 ? mst[c[f[delta][m]].s] : run_mst(f[delta][m], mod));
        printf("%d\n", run_mst(f[delta][m], mod));
    }
}
