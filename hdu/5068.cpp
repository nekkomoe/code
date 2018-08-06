#include "bits/stdc++.h"
using namespace std;
const int N = 5e4 + 10, p = 1e9 + 7;
typedef long long ll;

struct Mat {
    ll a[2][2];
    Mat() { memset(a, 0, sizeof a); }
    ll* operator [] (int i) { return a[i]; }
    Mat operator * (Mat b) {
        Mat rs;
        for(int i = 0 ; i < 2 ; ++ i)
            for(int j = 0 ; j < 2 ; ++ j)
                for(int k = 0 ; k < 2 ; ++ k)
                    rs[i][j] = (rs[i][j] + a[i][k] * b[k][j]) % p;
        return rs;
    }
} mat[N * 4];

int n, m;

#define lc (id << 1)
#define rc (id << 1 | 1)

void update(int id) { mat[id] = mat[lc] * mat[rc]; }

void build(int id, int l, int r) {
    int mid = (l + r) >> 1;
    if(l == r) mat[id][0][0] = mat[id][0][1] = mat[id][1][0] = mat[id][1][1] = 1;
    else build(lc, l, mid), build(rc, mid + 1, r), update(id);
}

void modify(int id, int l, int r, int pos, int x, int y) {
    int mid = (l + r) >> 1;
    if(l == r) return mat[id][x][y] ^= 1, void();
    if(pos <= mid) modify(lc, l, mid, pos, x, y);
    else modify(rc, mid + 1, r, pos, x, y); update(id);
}

Mat query(int id, int l, int r, int ql, int qr) {
    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) return mat[id];
    else if(qr <= mid) return query(lc, l, mid, ql, qr);
    else if(ql >= mid + 1) return query(rc, mid + 1, r, ql, qr);
    else return query(lc, l, mid, ql, mid) * query(rc, mid + 1, r, mid + 1, qr);
}

void sol() {
    memset(mat, 0, sizeof mat);
    build(1, 1, n);
    for(int i = 1, op, l, r, pos, x, y ; i <= m ; ++ i) {
        scanf("%d", &op);
        if(op == 0) {
            scanf("%d%d", &l, &r);
            Mat t = query(1, 1, n, l, r - 1);
            ll rs = 0;
            for(int i = 0 ; i < 2 ; ++ i) for(int j = 0 ; j < 2 ; ++ j) rs = (rs + t[i][j]) % p;
            printf("%lld\n", rs);
        } else {
            scanf("%d%d%d", &pos, &x, &y);
            modify(1, 1, n, pos, x - 1, y - 1);
        }
    }
}

int main() {
    while(scanf("%d%d", &n, &m) == 2) sol();
}

