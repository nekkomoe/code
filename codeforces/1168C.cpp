#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 3e5 + 10;

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

int n, q, a[N];
int lst[N][22], nek[22];
int nxt[N][22];

void runprog() {
    int x, y; scanf("%d%d", &x, &y);
    for(int i = 0 ; i <= 20 ; ++ i) {
        if((a[y] >> i) & 1) {
            if(nxt[x][i] <= y) {
                puts("Shi");
                return ;
            }
        }
    }
    puts("Fou");
}

int main() {
    scanf("%d%d", &n, &q);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }
    for(int i = 0 ; i <= 20 ; ++ i) {
        nek[i] = n + 10;
    }
    for(int i = n ; i >= 1 ; -- i) {
        memcpy(lst[i], nek, sizeof nek);
        for(int j = 0 ; j <= 20 ; ++ j) {
            if((a[i] >> j) & 1) {
                nxt[i][j] = i;
            } else {
                nxt[i][j] = n + 10;
                for(int k = 0 ; k <= 20 ; ++ k) {
                    if((a[i] >> k) & 1) {
                        if(nek[k] <= n) {
                            nxt[i][j] = min(nxt[i][j], nxt[nek[k]][j]);
                        }
                    }
                }
            }
        }
        for(int j = 0 ; j <= 20 ; ++ j) {
            if((a[i] >> j) & 1) {
                nek[j] = i;
            }
        }
        
    }
    while(q --) {
        runprog();
    }
}
