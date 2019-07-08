#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 3e5 + 10;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

ll getinv(ll n) {
    return pw(n, mod - 2);
}

void upd(ll &a, ll b) {
    a = (a + b) % mod;
}

int n, R;
struct P {
    int x, y;
} p[N];
bool operator < (P a, P b) {
    return make_pair(a.x, a.y) < make_pair(b.x, b.y);
}

#define lc (id << 1)
#define rc (id << 1 | 1)

const int T = 4e6 + 10;
int mx[T * 4], tag[T * 4];

void push(int id, int l, int r) {
    if(tag[id]) {
        mx[id] += tag[id];
        if(l < r) {
            tag[lc] += tag[id];
            tag[rc] += tag[id];
        }
        tag[id] = 0;
    }
}

void modify(int id, int l, int r, int ql, int qr, int x) {
    // printf("%d, [%d, %d], [%d, %d]\n", id, l, r, ql, qr);
    int mid = (l + r) >> 1;
    push(id, l, r);
    if(ql <= l && r <= qr) {
        tag[id] += x;
        return ;
    } else if(qr <= mid) {
        modify(lc, l, mid, ql, qr, x);
    } else if(ql >= mid + 1) {
        modify(rc, mid + 1, r, ql, qr, x);
    } else {
        modify(lc, l, mid, ql, mid, x);
        modify(rc, mid + 1, r, mid + 1, qr, x);
    }
    push(lc, l, mid), push(rc, mid + 1, r);
    mx[id] = max(mx[lc], mx[rc]);
}

int main() {
    scanf("%d%d", &n, &R);
    for(int i = 1 ; i <= n ; ++ i) {
        int x, y; scanf("%d%d", &x, &y);
        p[i].x = x + y;
        p[i].y = x - y;
    }
    // 用一个 [-R, R] 的正方形覆盖
    sort(p + 1, p + 1 + n);
    const int FKL = -2e6, FKR = 2e6;
    int ans = 0;
    for(int i = 1, j = 1 ; i <= n ; ++ i) {
        while(j <= i && p[j].x < p[i].x - 2 * R) {
            // remove p[j]
            modify(1, FKL, FKR, max(p[j].y - R, FKL), min(p[j].y + R, FKR), -1);
            ++ j;
        }
        modify(1, FKL, FKR, max(p[i].y - R, FKL), min(p[i].y + R, FKR), 1);
        ans = max(ans, mx[1]);
    }
    printf("%d\n", ans);
}

