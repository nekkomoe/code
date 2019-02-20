#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int n, k; ll ans;

struct Neko {
    int pos, len, q, l, r;
} neko[N];

int num[N], num_cnt;

bool neko_cmp(Neko a, Neko b) {
    return a.len > b.len;
}
bool neko_q(Neko a, Neko b) {
    return a.q < b.q;
}

int bit[N];
void add(int x, int y) {
    for( ; x <= n ; x += x & -x) {
        bit[x] += y;
    }
}
int ask(int x) {
    int res = 0;
    for( ; x ; x -= x & -x) {
        res += bit[x];
    }
    return res;
}
int ask(int l, int r) {
    return ask(r) - ask(l - 1);
}

int que[N], ql, qr;

void sol(int l, int r) {
    if(l >= r) return ;
    int mid = (l + r) >> 1;
    sol(l, mid), sol(mid + 1, r);
    int ql = l, qr = l - 1;
    for(int i = mid + 1 ; i <= r ; ++ i) {
        while(ql <= mid && neko[ql].q < neko[i].q - k) add(neko[ql ++].pos, -1);
        while(qr < mid && neko[qr + 1].q <= neko[i].q + k) add(neko[++ qr].pos, 1);
        ans += ask(neko[i].l, neko[i].r);
    }
    for(int i = ql ; i <= qr ; ++ i) add(neko[i].pos, -1);
    sort(neko + l, neko + r + 1, neko_q);
}

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d%d%d", &neko[i].pos, &neko[i].len, &neko[i].q);
        num[++ num_cnt] = neko[i].pos;
    }
    sort(num + 1, num + 1 + num_cnt);
    num_cnt = unique(num + 1, num + 1 + num_cnt) - num - 1;
    for(int i = 1 ; i <= n ; ++ i) {
        neko[i].l = lower_bound(num + 1, num + 1 + num_cnt, neko[i].pos - neko[i].len) - num;
        neko[i].r = upper_bound(num + 1, num + 1 + num_cnt, neko[i].pos + neko[i].len) - num - 1;
        neko[i].pos = lower_bound(num + 1, num + 1 + num_cnt, neko[i].pos) - num;
    }
    sort(neko + 1, neko + 1 + n, neko_cmp);
    sol(1, n);
    printf("%lld\n", ans);
}
