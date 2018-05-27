#include <bits/stdc++.h>
using namespace std;
const int N = 4e5 + 10, p = 1e9 + 7;
typedef long long ll;

struct Mat {
    ll a[2][2];
    Mat() { memset(a, 0, sizeof a); }
    ll* operator [] (int i) { return a[i]; }
    bool notI() {
        return !(a[0][0] == 1 && a[0][1] == 0
              && a[1][0] == 0 && a[1][1] == 1);
    }
    Mat operator * (Mat b) {
        Mat c;
        for(int i = 0 ; i < 2 ; ++ i)
            for(int j = 0 ; j < 2 ; ++ j)
                for(int k = 0 ; k < 2 ; ++ k)
                    c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % p;
        return c;
    }
    Mat operator + (Mat b) {
        Mat c;
        for(int i = 0 ; i < 2 ; ++ i)
            for(int j = 0 ; j < 2 ; ++ j)
                c[i][j] = (a[i][j] + b[i][j]) % p;
        return c;
    }
    void output() {
        puts("\n---");
        for(int i = 0 ; i < 2 ; ++ i, puts(""))
            for(int j = 0 ; j < 2 ; ++ j)
                printf("%d ", a[i][j]);
        puts("---\n");
    }
} mat[N * 4], M, B, tag[N * 4], I;

#define lc (id << 1)
#define rc (id << 1 | 1)

Mat pw(Mat a, ll b) {
    Mat c = I;
    for( ; b ; b >>= 1, a = a * a) if(b & 1) c = c * a;
    return c;
}

void update(int id) {
    mat[id] = mat[lc] + mat[rc];
}

void push(int id) {
    if(id && tag[id].notI()) {
        tag[lc] = tag[lc] * tag[id], tag[rc] = tag[rc] * tag[id];
        mat[lc] = mat[lc] * tag[id], mat[rc] = mat[rc] * tag[id];
        tag[id] = I;
    }
}

void build(int id, int l, int r) {
    int mid = (l + r) >> 1;
    tag[id] = I;
    if(l == r) {
        int x; scanf("%d", &x);
        mat[id] = B * pw(M, x - 1);
    } else {
        build(lc, l, mid), build(rc, mid + 1, r);
        update(id);
    }
}

void modify(int id, int l, int r, int ql, int qr, Mat x) {
    push(id);
    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) return tag[id] = tag[id] * x, mat[id] = mat[id] * x, void();
    else if(qr <= mid) modify(lc, l, mid, ql, qr, x);
    else if(ql >= mid + 1) modify(rc, mid + 1, r, ql, qr, x);
    else modify(lc, l, mid, ql, mid, x), modify(rc, mid + 1, r, mid + 1, qr, x); update(id);
}

ll query(int id, int l, int r, int ql, int qr) {
    push(id);
    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) return mat[id][0][1];
    else if(qr <= mid) return query(lc, l, mid, ql, qr);
    else if(ql >= mid + 1) return query(rc, mid + 1, r, ql, qr);
    else return (query(lc, l, mid, ql, mid) + query(rc, mid + 1, r, mid + 1, qr)) % p;
}

int n, m;

int main() {

#ifndef ONLINE_JUDGE
    freopen("data.in", "r", stdin);
#endif

    B[0][0] = 1, B[0][1] = 1;
    B[1][0] = 0, B[1][1] = 0;

    I[0][0] = 1, I[0][1] = 0;
    I[1][0] = 0, I[1][1] = 1;

    M[0][0] = 1, M[0][1] = 1;
    M[1][0] = 1, M[1][1] = 0;
    scanf("%d%d", &n, &m);
    build(1, 1, n);
    for(int i = 1, op, l, r, x ; i <= m ; ++ i) {
        scanf("%d%d%d", &op, &l, &r);
        if(op == 1) {
            scanf("%d", &x);
            modify(1, 1, n, l, r, pw(M, x));
        } else {
            printf("%I64d\n", query(1, 1, n, l, r));
        }
    }
}
