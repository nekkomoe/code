#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 2e5 + 10;

int n, m, k, s[N], len, bel[N];

ll ans[N], cnt[N];

struct Q { int l, r, id; } q[N];

bool operator < (Q a, Q b) { return bel[a.l] == bel[b.l] ? a.r < b.r : bel[a.l] < bel[b.l]; }

int main() {
    scanf("%d%d%d", &n, &m, &k);
    len = sqrt(n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &s[i]), s[i] ^= s[i - 1], bel[i] = (i - 1) / len + 1;
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }
    sort(q + 1, q + 1 + m);
    int l = 1, r = 0;
    ll ans = 0;
    for(int i = 1 ; i <= m ; ++ i) {
        while(r < q[i].r) {
            r ++, cnt[s[r]] ++, ans += cnt[s[r] ^ k];
            if((s[r] ^ k) == s[l - 1]) ans ++;
        }
        while(r > q[i].r) {
            ans -= cnt[s[r] ^ k], cnt[s[r]] --;
            if((s[r] ^ k) == s[l - 1]) ans --;
            r --;
        }
        while(l < q[i].l) {
            ans -= cnt[s[l - 1] ^ k], cnt[s[l]] --, l ++;
        }
        while(l > q[i].l) {
            l --, cnt[s[l]] ++, ans += cnt[s[l - 1] ^ k];
        }
        :: ans[q[i].id] = ans;
    }
    for(int i = 1 ; i <= m ; ++ i) {
        printf("%lld\n", :: ans[i]);
    }
}
