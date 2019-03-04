#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 100, mod = 1e9 + 7;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

int n, k;

vector<int> jzsdl;
namespace sdctrdsdzf {

    int fa[N];
    ll y[N]; // (x, y)
    ll a[N][N];

    ll getdet(int n) {
        ll flag = 0;
        for(int i = 1 ; i <= n ; ++ i) {
            int id = i;
            for(int j = i ; j <= n ; ++ j) {
                if(a[j][i]) {
                    id = j;
                    break;
                }
            }
            if(i != id) {
                for(int j = i ; j <= n ; ++ j) {
                    swap(a[i][j], a[id][j]);
                } flag ^= 1;
            }
            for(int j = i + 1 ; j <= n ; ++ j) {
                ll prod = pw(a[i][i], mod - 2) * a[j][i] % mod;
                for(int k = i ; k <= n ; ++ k) {
                    (a[j][k] -= prod * a[i][k] % mod) %= mod;
                }
            }
        }
        ll res = 1;
        for(int i = 1 ; i <= n ; ++ i) {
            res = res * a[i][i] % mod;
        }
        res = flag ? -res : res;

        return (res % mod + mod) % mod;
    }

    ll sol(int x) {
        memset(a, 0, sizeof a);
        for(int i = 1 ; i <= n ; ++ i) {
            for(int j = 1 ; j < i ; ++ j) {
                if(i == fa[j] || j == fa[i]) {
                    a[i][j] = a[j][i] = -1;
                    ++ a[i][i];
                    ++ a[j][j];
                } else {
                    a[i][j] = a[j][i] = -x;
                    a[i][i] += x;
                    a[j][j] += x;
                }
            }
        }


        return getdet(n - 1);
    }

    ll f[N];
    ll lg[N];

    void lglrcz() {
        for(int i = 1 ; i <= n ; ++ i) {
            ll t = y[i];
            for(int k = 0 ; k < n ; ++ k) lg[k] = 0;
            lg[0] = 1;
            for(int j = 1 ; j <= n ; ++ j) {
                if(i == j) continue;
                t = t * pw(i - j, mod - 2) % mod;
                for(int k = n - 1 ; k >= 0 ; -- k) {
                    if(k) {
                        lg[k] = (lg[k] * -j % mod + lg[k - 1]) % mod;
                    } else {
                        lg[k] = lg[k] * -j % mod;
                    }
                }
            }
            for(int k = 0 ; k < n ; ++ k) {
                (f[k] += (ll) lg[k] * t % mod) %= mod;
            }
        }
    }

    int runprog() {
        for(int i = 2 ; i <= n ; ++ i) {
            fa[i] = jzsdl[i - 2];
        }
        for(int i = 1 ; i <= n ; ++ i) {
            y[i] = sol(i);
        }
        lglrcz();

        ll ans = 0;
        for(int i = 0 ; i <= k ; ++ i) {
            ans = (ans + f[i]) % mod;
        }

        return (ans % mod + mod) % mod;
    }
}

struct TreeDistance {

    int countTrees(vector<int> _p, int _k) {
        n = _p.size() + 1, k = _k;
        for(int i = 2 ; i <= n ; ++ i) {
            int fa = _p[i - 2] + 1;
            jzsdl.push_back(fa);
        }

        return sdctrdsdzf :: runprog();
    }
};

// int main() {

// }
