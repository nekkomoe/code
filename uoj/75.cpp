#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 998244353, N = 1e5 + 10;

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

ll f[1010], g[1010]; // 生成树个数，以及生成树个数的倒数
ll a[20][20]; // 每张图的基尔霍夫矩阵
int ed[1010]; // 有多少条边
vector<pair<int, int> > tmp[1010]; // 边集

const int n = 12;

ll gause() {
    int n = :: n - 1;
    ll res = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        if(!a[i][i]) {
            for(int j = i + 1 ; j <= n ; ++ j) {
                if(a[j][i]) {
                    for(int k = 1 ; k <= n ; ++ k) {
                        swap(a[i][k], a[j][k]);
                    }
                    break;
                }
            }
        }
        if(!a[i][i]) {
            return 0;
        }
        for(int j = 1 ; j <= n ; ++ j) {
            if(j != i) {
                ll pro = a[j][i] * pw(a[i][i], mod - 2) % mod;
                for(int k = i ; k <= n ; ++ k) {
                    a[j][k] = ((a[j][k] - a[i][k] * pro % mod) % mod + mod) % mod;
                }
            }
        }
        res = res * a[i][i] % mod;
    }
    return (res % mod + mod) % mod;
}

unordered_map<ll, pair<int, int> > nek;

void init() {
    for(int ids = 1 ; ids <= 1000 ; ++ ids) {
        memset(a, 0, sizeof a);
        for(int i = 1 ; i <= n ; ++ i) {
            for(int j = i + 1 ; j <= n ; ++ j) {
                if(rand() % 2) {
                // if((rand() & 511) < 400) {
                    a[i][i] ++, a[j][j] ++;
                    a[i][j] --, a[j][i] --;
                    ++ ed[ids];
                    tmp[ids].emplace_back(i, j);
                }
            }
        }
        g[ids] = pw(f[ids] = gause(), mod - 2);
        // printf("ids = %d, f = %lld\n", ids, f[ids]);
        // assert(ed[ids] == tmp[ids].size());
    }
    for(int i = 1 ; i <= 1000 ; ++ i) {
        for(int j = i ; j <= 1000 ; ++ j) {
            nek[f[i] * f[j] % mod] = make_pair(i, j);
        }
    }
}

void print(int ids, int off) {
    for(auto e: tmp[ids]) {
        printf("%d %d\n", e.first + off, e.second + off);
    }
}

void runprog() {
    ll k; scanf("%lld", &k);
    for(int i = 1 ; i <= 1000 ; ++ i) {
        for(int j = i ; j <= 1000 ; ++ j) {
            if(g[i] && g[j]) {
                ll res = k * g[i] % mod * g[j] % mod;
                if(nek.count(res)) {
                    pair<int, int> ttt = nek[res];
                    int a = ttt.first, b = ttt.second;
                    printf("48 %d\n", ed[i] + ed[j] + ed[a] + ed[b] + 3);
                    print(i, 0);
                    print(j, 12);
                    print(a, 24);
                    print(b, 36);
                    puts("12 13");
                    puts("24 25");
                    puts("36 37");
                    return ;
                }
            }
        }
    }
    puts("QwQ");
    assert(0);
}

int main() {
    srand(19260817);
    init();
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
