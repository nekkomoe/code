#include <bits/stdc++.h>
using namespace std;
const int N = 15000 + 10, inf = 0x3f3f3f3f;
int q, maxv, T, d, vis[N * 4];

struct E { int v, w; };
vector<E> g[N * 4];
#define lc (id << 1)
#define rc (id << 1 | 1)
void ins(int id, int l, int r, int ql, int qr, E e) {
    int mid = (l + r) >> 1;

    // assert(id < N * 30);

    // cout << id << ' ' << l << ' ' << r << ' ' << ql << ' ' << qr << endl;
    if(ql <= l && r <= qr) return g[id].push_back(e), void();
    if(ql <= mid) ins(lc, l, mid, ql, qr, e);
    if(qr >= mid + 1) ins(rc, mid + 1, r, ql, qr, e);
}

vector<int> f[20];

void ask(int id, int l, int r, int pos, int v, int tot) {

    // assert(id < N * 30);

    int mid = (l + r) >> 1;
    if(!vis[id]) {
        f[tot] = f[tot - 1];
        vis[id] = 1;
        for(E e: g[id]) {
            for(int i = maxv ; i >= e.v ; -- i) {
                f[tot][i] = max(f[tot][i], f[tot][i - e.v] + e.w);
            }
        }
        g[id].clear();
    }
    // cout << id << ' ' << l << ' ' << r << ' ' << pos << ' ' << ' ' << v << ' ' << tot << endl;
    if(l == r) {
        d = f[tot][v] >= 0;
        printf("%d %d\n", d, d * f[tot][v]);
        d = T * (d ^ (d * f[tot][v]));
    } else {
        if(pos <= mid) ask(lc, l, mid, pos, v, tot + 1);
        else ask(rc, mid + 1, r, pos, v, tot + 1);
    }
}

int main () {
    // freopen("data.in", "r", stdin);
    // freopen("t.out", "w", stdout);
    scanf("%d%d%d", &q, &maxv, &T);
    for(int i = 1, op, v, w, e ; i <= q ; ++ i) {
        scanf("%d%d", &op, &v);
        if(op == 1) {
            scanf("%d%d", &w, &e);
            ins(1, 1, q, i, e - d, (E) { v - d, w - d });
        } else {
            f[0].resize(maxv + 1);
            for(int j = 0 ; j <= maxv ; ++ j) f[0][j] = -inf;
            f[0][0] = 0;
            ask(1, 1, q, i, v - d, 1);
        }
    }
}