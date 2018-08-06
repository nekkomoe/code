%:pragma GCC optimize(2)
%:pragma GCC optimize("Ofast")

#include "bits/stdc++.h"
using namespace std;
// 137 149
const int N = 2e5 + 10, mod = 998244353;
typedef unsigned long long ll;
const ll base = 137;
ll pw[N];
int n, m, a[N], lst[N], nxt[N], seq[N];
char s[(int) 1e7 + 10];

//map<ll, int> cnt[16777217];

int head[16777217], rest[16777217], val[16777217], tot;
ll to[16777217];

inline void ins(ll x, int c) {
    int u = x & 16777215;
    for(int i = head[u] ; i ; i = rest[i]) {
        if(to[i] == x) {
            val[i] += c;
            return ;
        }
    }
    to[++ tot] = x, val[tot] = c, rest[tot] = head[u], head[u] = tot;
}

inline int query(ll x) {
    for(int i = head[x & 16777215] ; i ; i = rest[i])
        if(to[i] == x)
            return val[i];
    return 0;
}

inline void fafa(int x, int y) {
    int bef_tot = 0, aft_tot = 0;
    for(int u = x ; bef_tot <= 50 && u ; u = lst[u])
        seq[++ bef_tot] = a[u];
    reverse(seq + 1, seq + 1 + bef_tot);
    int tot = bef_tot;
    for(int u = y ; aft_tot <= 50 && u ; u = nxt[u])
        seq[++ tot] = a[u];
    for(int i = 1 ; i <= bef_tot ; ++ i) {
        ll hs = 0;
        for(int j = i ; j <= tot ; ++ j) {
            hs = hs * base + seq[j];
            if(j - i + 1 > 50) break;
            if(j > bef_tot) ins(hs, 1);
        }
    }
}

inline void gygy(int x, int y) {
    int bef_tot = 0, aft_tot = 0;
    for(int u = x ; bef_tot <= 50 && u ; u = lst[u])
        seq[++ bef_tot] = a[u];
    reverse(seq + 1, seq + 1 + bef_tot);
    int tot = bef_tot;
    for(int u = y ; aft_tot <= 50 && u ; u = nxt[u])
        seq[++ tot] = a[u];;
    for(int i = 1 ; i <= bef_tot ; ++ i) {
        ll hs = 0;
        for(int j = i ; j <= tot ; ++ j) {
            hs = hs * base + seq[j];
            if(j - i + 1 > 50) break;
            if(j > bef_tot) ins(hs, -1);
        }
    }
}

inline void read(int &x) {
    char c = x = 0;
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

int main() {
    pw[0] = 1; for(int i = 1 ; i < N ; ++ i) pw[i] = pw[i - 1] * base;
    read(n), read(m);
    for(int i = 1 ; i <= n ; ++ i) read(a[i]), ins(a[i], 1);
    for(int i = 1 ; i <= m ; ++ i) {
        int op, x, y, k;
        read(op);
        if(op == 1) {
            read(x), read(y);
            lst[y] = x, nxt[x] = y;
            fafa(x, y);
        } else if(op == 2) {
            read(x);
            int y = nxt[x];
            lst[y] = 0, nxt[x] = 0;
            gygy(x, y);
        } else {
            scanf("%s", s + 1), read(k);
            int ans = 1, len = strlen(s + 1);
            ll hs = 0;
            if(k <= len) {
                for(int i = 1 ; i <= k ; ++ i)
                    hs = hs * base + s[i] - '0';
                ans = query(hs);
                for(int i = 2 ; i + k - 1 <= len ; ++ i) {
                    hs = (hs - (s[i - 1] - '0') * pw[k - 1]) * base + s[i + k - 1] - '0';
                    ans = ((long long) ans * query(hs)) % mod;
                }
            } else ans = 0;
            printf("%d\n", ans);
        }
    }
}
