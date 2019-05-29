#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
typedef long long ll;

struct OPS {
    int op;
    int p, d;
    int l, r;
} ops[N];

int n, m;
ll x[N]; int ids[N];
vector<ll> num;
int lim, rev[N];

int getval(ll x) {
    return lower_bound(num.begin(), num.end(), x) - num.begin() + 1;
}
void lsh() {
    vector<ll> x(n + 10);
    for(int i = 1 ; i <= n ; ++ i) {
        x[i] = :: x[i];
        num.push_back(x[i]);
    }
    for(int i = 1 ; i <= m ; ++ i) {
        if(ops[i].op == 1) {
            num.push_back(x[ops[i].p] += ops[i].d);
        } else {
            num.push_back(ops[i].l);
            num.push_back(ops[i].r);
        }
    }
    sort(num.begin(), num.end());
    num.erase(unique(num.begin(), num.end()), num.end());
    lim = num.size();
    for(int i = 1 ; i <= lim ; ++ i) {
        rev[i] = num[i - 1];
    }
}

#define lc (id << 1)
#define rc (id << 1 | 1)

int a[N];

struct T {
    ll num, sum, ans;
} val[N];

T operator + (T a, T b) {
    return (T) { a.num + b.num, a.sum + b.sum, b.sum * a.num - a.sum * b.num + a.ans + b.ans };
}

T build(int id, int l, int r) {
    int mid = (l + r) >> 1;
    return l == r ?  val[id] = (T) { a[l], a[l] * rev[l], 0 } : val[id] = build(lc, l, mid) + build(rc, mid + 1, r);
}

void modify(int id, int l, int r, int pos, int nek) {
    int mid = (l + r) >> 1;
    if(l == r) {
        val[id].num += nek;
        val[id].sum = val[id].num * rev[l];
        val[id].ans = 0;
        return ;
    } else if(pos <= mid) {
        modify(lc, l, mid, pos, nek);
    } else {
        modify(rc, mid + 1, r, pos, nek);
    }
    val[id] = val[lc] + val[rc];
}

T ask(int id, int l, int r, int ql, int qr) {

    // printf("id = %d, %d, %d, %d, %d\n", id, l, r, ql, qr);
    // system("sleep 0.5");

    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) {
        return val[id]; 
    } else if(qr <= mid) {
        return ask(lc, l, mid, ql, qr);
    } else if(ql >= mid + 1) {
        return ask(rc, mid + 1, r, ql, qr);
    } else {
        return ask(lc, l, mid, ql, mid) + ask(rc, mid + 1, r, mid + 1, qr);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &x[i]);
    }
    scanf("%d", &m);
    for(int i = 1 ; i <= m ; ++ i) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        ops[i] = (OPS) { a, b, c, b, c };
    }
    lsh();
    for(int i = 1 ; i <= n ; ++ i) {
        ids[i] = getval(x[i]);
        a[ids[i]] = 1;
    }
    build(1, 1, lim);
    for(int i = 1 ; i <= m ; ++ i) {
        int op = ops[i].op;
        if(op == 1) {
            int p = ops[i].p, d = ops[i].d;
            int aft = getval(x[p] += d);
            modify(1, 1, lim, ids[p], -1);
            ids[p] = aft;
            modify(1, 1, lim, ids[p], 1);
        } else {
            int l = getval(ops[i].l), r = getval(ops[i].r);
            T res = ask(1, 1, lim, l, r);
            printf("%lld\n", res.ans);
        }
    }
}
