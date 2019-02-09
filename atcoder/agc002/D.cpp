#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int fa[N], sz[N], n, m, q, ans[N], p;
struct E { int u, v; } e[N];
struct ASK { int x, y, z, id; };
struct LINE { int l, r, ql, qr; };
vector<ASK> ask[2];
vector<LINE> ln[2];
int get(int x) { return x == fa[x] ? x : fa[x] = get(fa[x]); }
void merge(int x, int y) {
    x = get(x), y = get(y);
    if(x == y) return ;
    fa[x] = y;
    sz[y] += sz[x];
}
int calc(int x, int y) {
    x = get(x), y = get(y);
    if(x != y) {
        return sz[x] + sz[y];
    } else {
        return sz[x];
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%d%d", &e[i].u, &e[i].v);
    }
    scanf("%d", &q);
    for(int i = 1, x, y, z ; i <= q ; ++ i) {
        scanf("%d%d%d", &x, &y, &z);
        ask[0].push_back((ASK) { x, y, z, i });
    }
    ln[0].push_back((LINE) { 0, q - 1, 0, m });
    while(ln[p].size()) {
        ask[p ^ 1].clear(), ln[p ^ 1].clear();
        for(int i = 1 ; i <= n ; ++ i) {
            fa[i] = i;
            sz[i] = 1;
        }
        int pos = 1;
        for(int i = 0 ; i < ln[p].size() ; ++ i) {
            int l = ln[p][i].l, r = ln[p][i].r, ql = ln[p][i].ql, qr = ln[p][i].qr;
            if(ql == qr) {
                for(int j = l ; j <= r ; ++ j) {
                    ans[ask[p][j].id] = ql;
                }
                continue;
            }
            int mid = (ql + qr) >> 1;
            for( ; pos <= mid ; ++ pos) {
                merge(e[pos].u, e[pos].v);
            }
            int cnt = 0;
            for(int j = l ; j <= r ; ++ j) {
                int x = ask[p][j].x, y = ask[p][j].y, z = ask[p][j].z;
                if(calc(x, y) >= z) {
                    ++ cnt;
                    ask[p ^ 1].push_back(ask[p][j]);
                }
            }
            if(cnt) {
                ln[p ^ 1].push_back((LINE) { ask[p ^ 1].size() - cnt, ask[p ^ 1].size() - 1, ql, mid });
            }
            cnt = 0;
            for(int j = l ; j <= r ; ++ j) {
                int x = ask[p][j].x, y = ask[p][j].y, z = ask[p][j].z;
                if(calc(x, y) < z) {
                    ++ cnt;
                    ask[p ^ 1].push_back(ask[p][j]);
                }
            }
            if(cnt) {
                ln[p ^ 1].push_back((LINE) { ask[p ^ 1].size() - cnt, ask[p ^ 1].size() - 1, mid + 1, qr });
            }
        }
        p ^= 1;
    }

    for(int i = 1 ; i <= q ; ++ i) {
        printf("%d\n", ans[i]);
    }
}
