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

queue<int> que[N];

int n, a[N], b[N];

int val[N * 10];
#define lc (id << 1)
#define rc (id << 1 | 1)
void build(int id, int l, int r) {
    int mid = (l + r) >> 1;
    if(l == r) {
        val[id] = a[l];
    } else {
        build(lc, l, mid);
        build(rc, mid + 1, r);
        val[id] = min(val[lc], val[rc]);
    }
}

int ask(int id, int l, int r, int ql, int qr) {
    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) {
        return val[id];
    } else if(qr <= mid) {
        return ask(lc, l, mid, ql, qr);
    } else if(ql >= mid + 1) {
        return ask(rc, mid + 1, r, ql, qr);
    } else {
        return min(ask(lc, l, mid, ql, mid), ask(rc, mid + 1, r, mid + 1, qr));
    }
}
void modify(int id, int l, int r, int pos, int x) {
    int mid = (l + r) >> 1;
    if(l == r) {
        val[id] = x;
        return ;
    } else if(pos <= mid) {
        modify(lc, l, mid, pos, x);
    } else {
        modify(rc, mid + 1, r, pos, x);
    }
    val[id] = min(val[lc], val[rc]);
}

void runprog() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        que[a[i]].push(i);
    }
    val[0] = 0x3f3f3f3f;
    build(1, 1, n);

    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &b[i]);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        if(que[b[i]].empty()) {
            puts("NO");
            return ;
        } else {
            int pos = que[b[i]].front();
            que[b[i]].pop();
            modify(1, 1, n, pos, 0x3f3f3f3f);
            int mn = ask(1, 1, n, 1, pos);
            if(mn < b[i]) {
                puts("NO");
                return ;
            }
        }
    }
    puts("YES");
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
        for(int i = 1 ; i <= n ; ++ i) {
            que[i] = queue<int>();
        }
    }
}
