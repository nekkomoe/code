#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 110;
ll n, m, pw[N], ln, lm, dign[N], digm[N], nxt[N];
typedef pair<ll, ll> pll;

// (n+1)k-sum a_i
ll calc(ll k, ll s) {
    return (((n + 1) % mod * k % mod - s) % mod + (n % mod)) % mod;
}

namespace m_gt_1e5 {
    set<ll> st;

    void dfs(int stp, ll sum, int has) {
        if(stp < 0 || sum > n || (has == 0 && stp - lm < 0)) {
            return ;
        } else if(stp == 0) {
            if(has) {
                st.insert(sum);
            }
        } else {
            for(int i = 0 ; i <= 9 ; ++ i) {
                dfs(stp - 1, sum * 10 + i, has);
            }
            if((__int128) sum * pw[lm] + m <= n) {
                dfs(stp - lm, sum * pw[lm] + m, 1);
            }
        }
    }

    void runprog() {
        for(ll i = m ; i <= n ; i += m) st.insert(i);
        dfs(ln, 0, 0);
        ll sum = 0;
        for(ll x: st) (sum += x % mod) %= mod;
        ll ans = calc(st.size(), sum);
        ans = (ans % mod + mod) % mod;
        printf("%lld\n", ans);
    }
}

namespace m_le_1e5 {
    // 长度，next数组的位置，数值模m，是否之前完全匹配过

    bool vis[12][12][int(1e5) + 10][2];
    pll f[12][12][int(1e5) + 10][2];
    #define state [stp][p][val_mod][has]
    pll dfs(int stp, int p, int val_mod, int lim, int led, int has) {
        if(stp == 0) {
            return make_pair(led == 0 && (has || val_mod == 0), 0);
        } else if(!lim && !led && vis state) {
            return f state;
        } else {
            pll res;
            for(int i = (lim ? dign[stp] : 9) ; i >= 0 ; -- i) {
                int j = p, canhas = 0; while(j && digm[j + 1] != i) j = nxt[j];
                if(digm[j + 1] == i) ++ j;
                if(j == lm) j = nxt[j], canhas = 1;
                pll tmp = dfs(stp - 1, j, (val_mod * 10 + i) % m, lim && i == dign[stp], led && i == 0, has || canhas);
                (res.first += tmp.first) %= mod;
                (res.second += tmp.second) %= mod;
                (res.second += i * pw[stp - 1] % mod * tmp.first % mod) %= mod;
            }
            if(!lim && !led) {
                vis state = 1;
                f state = res;
            }
            return res;
        }
    }
    #undef state

    void runprog() {
        pll res = dfs(ln, 0, 0, 1, 1, 0);
        ll ans = calc(res.first, res.second);
        ans = (ans % mod + mod) % mod;
        printf("%lld\n", ans);
    }
}

namespace m_le_99 {
    // 长度，next数组的位置，数值模m，数位和模m，是否之前完全匹配过

    bool vis[12][12][110][110][2];
    pll f[12][12][110][110][2];
    #define state [stp][p][val_mod][dig_mod][has]
    pll dfs(int stp, int p, int val_mod, int dig_mod, int lim, int led, int has) {
        if(stp == 0) {
            return make_pair(led == 0 && (has || val_mod == 0 || dig_mod == 0), 0);
        } else if(!lim && !led && vis state) {
            return f state;
        } else {
            pll res;
            for(int i = (lim ? dign[stp] : 9) ; i >= 0 ; -- i) {
                int j = p, canhas = 0; while(j && digm[j + 1] != i) j = nxt[j];
                if(digm[j + 1] == i) ++ j;
                if(j == lm) j = nxt[j], canhas = 1;
                pll tmp = dfs(stp - 1, j, (val_mod * 10 + i) % m, (dig_mod + i) % m, lim && i == dign[stp], led && i == 0, has || canhas);
                (res.first += tmp.first) %= mod;
                (res.second += tmp.second) %= mod;
                (res.second += i * pw[stp - 1] % mod * tmp.first % mod) %= mod;
            }
            if(!lim && !led) {
                vis state = 1;
                f state = res;
            }
            return res;
        }
    }
    #undef state

    void runprog() {
        pll res = dfs(ln, 0, 0, 0, 1, 1, 0);
        ll ans = calc(res.first, res.second);
        ans = (ans % mod + mod) % mod;
        printf("%lld\n", ans);
    }
}

void init() {
    for(ll x = n ; x ; x /= 10) dign[++ ln] = x % 10;
    for(ll x = m ; x ; x /= 10) digm[++ lm] = x % 10;
    reverse(digm + 1, digm + 1 + lm);
    nxt[1] = 0; for(int i = 2, j = 0 ; i <= lm ; ++ i) {
        while(j && digm[j + 1] != digm[i]) j = nxt[j];
        if(digm[j + 1] == digm[i]) ++ j;
        nxt[i] = j;
    }
    for(int i = pw[0] = 1 ; i <= 12 ; ++ i) pw[i] = pw[i - 1] * 10;
}

int main() {
    scanf("%lld%lld", &n, &m);
    init();
    if(m <= 99) {
        m_le_99 :: runprog();
    } else if(m <= 100000) {
        m_le_1e5 :: runprog();
    } else {
        m_gt_1e5 :: runprog();
    }
}
