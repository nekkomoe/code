#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 45, mod = 1e9 + 7, base = 45;

ll pw[N];

int n;
char str[110];
map<ll, ll> mem[N];

void upd(ll &x, ll y) {
    x = (x + y) % mod;
}

ll dfs(int stp, ll S) {
    if(stp == n + 1) return 1;
    if(mem[stp].count(S)) return mem[stp][S];
    ll res = 0;

    ll bak = S;
    ll pos = S % base; S /= base;
    ll len = S % base; S /= base;

    if(pos > len) {
        printf("len = %lld, pos = %lld\n", len, pos);
        assert(0);
    }

    if(str[stp] == '0') {
        // no 2

        // another
        for(int L = 1 ; L <= 6 ; ++ L) {
            ll sum = 0, cnt = ((S / pw[L]) % base - (L == len));
            if(cnt) {
                for(int P = 1 ; P <= L ; ++ P) {
                    ll T = S;
                    T -= pw[len];
                    T += pw[pos - 1];
                    T += pw[len - pos];
                    T = T * base + L;
                    T = T * base + P;
                    upd(sum, dfs(stp + 1, T));
                }
                upd(res, sum * cnt % mod);
            }
        }

        // up
        for(int L = 1 ; L <= pos - 2 ; ++ L) {
            ll T = S;
            T -= pw[len];
            T += pw[pos - 1];
            T += pw[len - pos];
            T = T * base + pos - 1;
            T = T * base + L;
            upd(res, dfs(stp + 1, T));
        }

        // down
        for(int L = pos + 2 ; L <= len ; ++ L) {
            ll T = S;
            T -= pw[len];
            T += pw[pos - 1];
            T += pw[len - pos];
            T = T * base + len - pos;
            T = T * base + L - pos;
            upd(res, dfs(stp + 1, T));
        }
    } else {
        // yes 2

        // up
        if(pos > 1) {
            ll T = S;
            T -= pw[len];
            T += pw[pos - 1];
            T += pw[len - pos];
            T = T * base + pos - 1;
            T = T * base + pos - 1;
            upd(res, dfs(stp + 1, T));
        }

        // down
        if(pos < len) {
            ll T = S;
            T -= pw[len];
            T += pw[pos - 1];
            T += pw[len - pos];
            T = T * base + len - pos;
            T = T * base + 1;
            upd(res, dfs(stp + 1, T));
        }
    }

    return mem[stp][bak] = res;
}

int main() {
    scanf("%d%s", &n, str + 2), str[1] = '0';
    for(int i = (pw[1] = 1) + 1 ; i <= 40 ; ++ i) {
        pw[i] = pw[i - 1] * base % mod;
    }

    ll sta = pw[1];
    for(int i = 1 ; i <= n ; i += 2) {
        int len = 0;
        for(int j = i ; j <= n ; j *= 2) {
            ++ len;
        }
        sta += pw[len];
    }
    sta = sta * base + 1;
    sta = sta * base + 1;

    printf("%lld\n", (dfs(1, sta) % mod + mod) % mod);
}
