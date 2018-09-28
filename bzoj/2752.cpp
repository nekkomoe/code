// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10; 

ll sum[N * 10], sum1[N * 10], sum2[N * 10], tag[N * 10];

#define lc (id << 1)
#define rc (id << 1 | 1)

ll calc1(ll l, ll r) {
    return (l + r) * (r - l + 1) / 2;
}

ll c2(ll n) {
    return (2 * n + 1) * n * (n + 1) / 6;
}

ll calc2(ll l, ll r) {
    return c2(r) - c2(l - 1);
}

void push(int id, int l, int r) {
    if(tag[id]) {
        tag[lc] += tag[id], tag[rc] += tag[id];
        ll x = tag[id];
        
        sum[id] += x * (r - l + 1);
        
        sum1[id] += x * calc1(l, r);
        
        sum2[id] += x * calc2(l, r);
        
        tag[id] = 0;
    }
}

void update(int id, int l, int r) {
    int mid = (l + r) >> 1;
    push(id, l, r), push(lc, l, mid), push(rc, mid + 1, r);
    sum[id] = sum[lc] + sum[rc];
    sum1[id] = sum1[lc] + sum1[rc];
    sum2[id] = sum2[lc] + sum2[rc];
}

void modify(int id, int l, int r, int ql, int qr, ll x) {
//	for(int i = ql ; i <= qr ; ++ i)
//		sum[i] += x, sum1[i] += x * i, sum2[i] += x * i * i;
//	return ;
	
    int mid = (l + r) >> 1;
    push(id, l, r);
    if(ql <= l && r <= qr) {
        tag[id] += x;
        return ;
    } else if(qr <= mid) {
        modify(lc, l, mid, ql, qr, x);
    } else if(ql > mid) {
        modify(rc, mid + 1, r, ql, qr, x);
    } else {
        modify(lc, l, mid, ql, mid, x), modify(rc, mid + 1, r, mid + 1, qr, x);
    }
    update(id, l, r);
}

ll s, s1, s2;

void query(int id, int l, int r, int ql, int qr) {
	
//	for(int i = ql ; i <= qr ; ++ i)
//		s += sum[i], s1 += sum1[i], s2 += sum2[i];
//	return ;
	
    int mid = (l + r) >> 1;
    push(id, l, r);
    if(ql <= l && r <= qr) s += sum[id], s1 += sum1[id], s2 += sum2[id];
    else if(qr <= mid) query(lc, l, mid, ql, qr);
    else if(ql > mid) query(rc, mid + 1, r, ql, qr);
    else query(lc, l, mid, ql, mid), query(rc, mid + 1, r, mid + 1, qr);
}

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
//	freopen("std.in", "r", stdin);
//	freopen("std.out", "w", stdout);
    int n, m; scanf("%d%d", &n, &m);
    for(int i = 1, l, r, v ; i <= m ; ++ i) {
        char op[10];
        scanf("%s", op);
        if(op[0] == 'C') {
            scanf("%d%d%d", &l, &r, &v);
            modify(1, 1, n, l, r - 1, v);
        } else {
            scanf("%d%d", &l, &r), -- r;
            s = s1 = s2 = 0;
            query(1, 1, n, l, r);
            ll down = 1ll * (r - l + 2) * (r - l + 1) / 2;
            ll up = s * (r + 1) * (1 - l) + (l + r) * s1 - s2;
            ll d = gcd(up, down);
            up /= d, down /= d;
            printf("%lld/%lld\n", up, down);
        }
    }
}
