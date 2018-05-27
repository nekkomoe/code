#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e5 + 10, p = 1e9 + 7;

struct Mat {
    ll a[3][3];
    Mat() { memset(a, 0, sizeof a); }
    ll* operator [] (int i) { return a[i]; }
    Mat operator * (Mat b) {
        Mat c;
        for(int i = 0 ; i < 3 ; ++ i)
            for(int j = 0 ; j < 3 ; ++ j)
                for(int k = 0 ; k < 3 ; ++ k)
                    c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % p;
        return c;
    }
    void output() {
        puts("");
        for(int i = 0 ; i < 3 ; ++ i, puts(""))
            for(int j = 0 ; j < 3 ; ++ j)
                printf("%lld ", a[i][j]);
        puts("");
    }
} mat[N * 10], I, M0, M1;

char s[N];
int rev[N * 10], n, m;

#define lc (id << 1)
#define rc (id << 1 | 1)

void push(int id) {
    if(rev[id]) {
        rev[lc] ^= 1, rev[rc] ^= 1, rev[id] = 0;
        for(int i = 0 ; i < 3 ; ++ i) swap(mat[id][i][0], mat[id][i][1]);
        for(int i = 0 ; i < 3 ; ++ i) swap(mat[id][0][i], mat[id][1][i]);
    }
}

void update(int id) {
    push(id), push(lc), push(rc);
    mat[id] = mat[lc] * mat[rc];
}

void build(int id, int l, int r) {
    int mid = (l + r) >> 1;
    if(l == r) mat[id] = s[l] == '0' ? M0 : M1;
    else build(lc, l, mid), build(rc, mid + 1, r), update(id);
}

Mat query(int id, int l, int r, int ql, int qr) {
    int mid = (l + r) >> 1;
    push(id);
    if(ql > r || qr < l) return I;
    else if(ql <= l && r <= qr) return mat[id];
    else return query(lc, l, mid, ql, qr) * query(rc, mid + 1, r, ql, qr);
}

void modify(int id, int l, int r, int ql, int qr) {
    int mid = (l + r) >> 1;
    push(id);
    if(ql > r || qr < l) return ;
    else if(ql <= l && r <= qr) rev[id] ^= 1;
    else modify(lc, l, mid, ql, qr), modify(rc, mid + 1, r, ql, qr), update(id);
}

void sol() {
    memset(mat, 0, sizeof mat), memset(rev, 0, sizeof rev);
    scanf("%d%d%s", &n, &m, s + 1);
    build(1, 1, n);
    for(int i = 1, op, l, r ; i <= m ; ++ i) {
        scanf("%d%d%d", &op, &l, &r);
        if(op == 1) {
            modify(1, 1, n, l, r);
        } else {
            Mat t = query(1, 1, n, l, r);
            printf("%lld\n", (t[2][0] + t[2][1]) % p);
        }
    }
}

int main() {
    I[0][0] = 1, I[0][1] = 0, I[0][2] = 0;
    I[1][0] = 0, I[1][1] = 1, I[1][2] = 0;
    I[2][0] = 0, I[2][1] = 0, I[2][2] = 1;

    M0[0][0] = 1, M0[0][1] = 0, M0[0][2] = 0;
    M0[1][0] = 1, M0[1][1] = 1, M0[1][2] = 0;
    M0[2][0] = 1, M0[2][1] = 0, M0[2][2] = 1;

    M1[0][0] = 1, M1[0][1] = 1, M1[0][2] = 0;
    M1[1][0] = 0, M1[1][1] = 1, M1[1][2] = 0;
    M1[2][0] = 0, M1[2][1] = 1, M1[2][2] = 1;

    int T; scanf("%d", &T);
    while(T --) sol();
}

