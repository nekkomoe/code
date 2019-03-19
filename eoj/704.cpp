#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 2e5 + 10, mod = 1e9 + 7;

struct NEKO {
    int x, v;
} neko[N];

bool cmpx(NEKO a, NEKO b) {
    return a.x < b.x;
}

int L[N], R[N], vis[N], n;
int num[N], num_cnt;

ll bit[N];
void add(int x, ll y) {
    for( ; x <= num_cnt ; x += x & -x) {
        (bit[x] += y) %= mod;
    }
}
ll ask(int x) {
    if(x <= 0) return 0;
    ll res = 0;
    for( ; x ; x -= x & -x) {
        (res += bit[x]) %= mod;
    }
    return res;
}

vector<int> pak[N];
ll f[N];

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d%d", &neko[i].x, &neko[i].v);
        num[i] = neko[i].v;
    }
    sort(neko + 1, neko + 1 + n, cmpx);
    sort(num + 1, num + 1 + n);
    num_cnt = unique(num + 1, num + 1 + n) - num - 1;
    for(int i = 1 ; i <= n ; ++ i) {
        neko[i].v = lower_bound(num + 1, num + 1 + num_cnt, neko[i].v) - num;
        L[i] = max(L[i - 1], neko[i].v);
    }
    R[n] = neko[n].v; for(int i = n - 1 ; i ; -- i) {
        R[i] = min(R[i + 1], neko[i].v);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        pak[L[i]].push_back(R[i]);
    }
    for(int i = 1 ; i <= num_cnt ; ++ i) {
        for(int t: pak[i]) {
            ll val = (ask(i) - ask(t - 2) + (t == 1)) % mod;
            (f[i] += val) %= mod;
            add(i, val);
        }
    }
    printf("%lld\n", (f[num_cnt] + mod) % mod);
}
