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

int n, k;
void upd(ll &x, ll y) {
    x = (x + y) % mod;
}

const int NTTLEN = N * 10;

ll motz[NTTLEN];
int a[NTTLEN], b[NTTLEN];

ll f[int(1e7) + 10];

void initmoth(int n) {
    motz[0] = motz[1] = 1;
    for(int i = 1 ; i < n ; ++ i) {
        motz[i + 1] = ((2 * i + 3) % mod * motz[i] % mod + 3 * i * motz[i - 1] % mod) % mod * pw(i + 3, mod - 2) % mod;
    }
    for(int i = n ; i >= 0 ; -- i) {
        motz[i] = (i >= 2 ? motz[i - 2] : 0);
    }
    motz[1] = 1;
    
    // 常数项为0 
    // (xA(x))^k = x^kA(x)^k
}

void init(int n, int k) {
    initmoth(n);    
    
    -- k;
    f[0] = 1;
    a[0] = 1;
    for(int i = 0 ; i <= n ; ++ i) b[i] = motz[i + 1];
    for( ; k ; k >>= 1) {
        if(k & 1) {
            for(int i = n ; i >= 0 ; -- i) {
                ll s = 0;
                for(int j = 0 ; j <= i ; ++ j) {
                    s = (s + (ll) a[j] * b[i - j] % mod) % mod;
                }
                a[i] = s;
            }
        }
        for(int i = n ; i >= 0 ; -- i) {
            ll s = 0;
            for(int j = 0 ; j <= i ; ++ j) {
                s = (s + (ll) b[j] * b[i - j] % mod) % mod;
            }
            b[i] = s;
        }
    }
    for(int i = 0 ; i <= n ; ++ i) {
        f[i] = a[i];
    }
}














// 对这个鬼畜玩意跑gause 
vector<ll> ext_set; // 如果有自由元，那么就xjb搞一个扔进去 
vector<vector<ll> > gause(vector<vector<ll> > a) {
    ext_set.clear();
    
    
    int n = a[0].size() - 1; // [0, n]，sum xi*ti = ci 
    int m = a.size(); // [0, m - 1]
    
    for(int i = 0 ; i < m ; ++ i) {
        if(i == n) {
            break;
        }
        
        MEGUMIN:
        if(!a[i][i]) {
            for(int j = m - 1 ; j > i ; -- j) {
                if(a[j][i]) {
                    for(int k = i ; k <= n ; ++ k) {
                        swap(a[i][k], a[j][k]);
                    }
                    break;
                }
            }
        }
        if(a[i][i]) {
            for(int j = i + 1 ; j < m ; ++ j) {
                ll pro = a[j][i] * getinv(a[i][i]) % mod;
                for(int k = i ; k <= n ; ++ k) {
                    a[j][k] = (a[j][k] - (ll) a[i][k] * pro % mod) % mod;
                }
            }
        } else {
            ll val = rand() % 10 + 1; // a[i][i] = val;
            ext_set.clear();
            for(int i = 0 ; i <= n ; ++ i) {
                ext_set.push_back(0);
            }
            ext_set[i] = 1;
            ext_set[n] = val;
//            puts("gg");
            
            a.push_back(ext_set);
            ++ m;
            goto MEGUMIN;
            return a;
        }
    }
    
    for(int i = n - 1 ; i >= 0 ; -- i) {
        if(a[i][i]) {
            a[i][n] = a[i][n] * getinv(a[i][i]) % mod;
            a[i][i] = 1;
            for(int j = i - 1 ; j >= 0 ; -- j) {
                a[j][n] = (a[j][n] - a[j][i] * a[i][n] % mod) % mod;
                a[j][i] = 0;
            }
        }
    }
    
    return a; // 返回消完的矩阵 
}

ll thecoefs[int(1e7) + 10];



void runinv(int n) {
    static ll inv[int(1e7) + 10];
    static ll prod[int(1e7) + 10];
//    for(int i = 1 ; i <= n ; ++ i) {
//        thecoefs[i] = getinv(thecoefs[i]);
//    }
//    return ;
    
    if(!n) return ;
//    printf("top = %d\n", n);
    
    prod[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        prod[i] = prod[i - 1] * thecoefs[i] % mod;
    }
    inv[n] = pw(prod[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) {
        inv[i] = inv[i + 1] * thecoefs[i + 1] % mod;
    }
    for(int i = 1 ; i <= n ; ++ i) {
        thecoefs[i] = inv[i] * prod[i - 1] % mod;
    }
}

int main() {
//    n = 10000000, k = 100000;
    scanf("%d%d", &n, &k);
    init(30, k);
    vector<vector<ll> > a;
    int DEG = 1; // 最高次项 [0, DEG] 
    int L = 2; // 递推长度
    // sum(i=0~L) sum(j=0~DEG) eij * (n-i)^j * f(n-i)  =  0

    DEG = 2, L = 3; // 调参现场 

    int START = max(k, L) + 5, END = START + (L + 1) * (DEG + 1) + 2;
    
    for(int n = START ; n <= END ; ++ n) {
        vector<ll> coef;
        for(int i = 0 ; i <= L ; ++ i) {
            for(int j = 0 ; j <= DEG ; ++ j) {
                coef.push_back(pw(n - i, j) * f[n - (k - 1) - i] % mod);
            }
        }
        coef.push_back(0); // sum = 0
        a.push_back(coef);
    }
    
    vector<vector<ll> > res = gause(a);
    
//    for(auto x: res) {
//        for(auto y: x) {
//            printf("%lld ", y);
//        }
//        puts("");
//    }
    
    if(1) {
        {
            int flag = 0;
            for(int j = 0 ; j <= DEG ; ++ j) {
                flag |= res[j][res[0].size() - 1] != 0;
            }
            assert(flag);
        }
        
        for(int n = START ; n <= END ; ++ n) {
            ll s = 0;
            for(int i = 0 ; i <= L ; ++ i) {
                for(int j = 0 ; j <= DEG ; ++ j) {
                    s += pw(n - i, j) * res[i * (DEG + 1) + j][res[0].size() - 1] % mod * f[n - (k - 1) - i] % mod;
                    s %= mod;
                }
            }
            s = (s % mod + mod) % mod;
            assert(s == 0);
        }
    }
    
    for(int i = k + 30 ; i >= 0 ; -- i) {
        if(i >= k - 1) {
            swap(f[i], f[i - (k - 1)]);
        } else {
            f[i] = 0;
        }
    }
    
    int top = 0;
    for(int n = k + 15 ; n <= :: n ; ++ n) {
        ll coef = 0;
        for(int i = 0 ; i <= L ; ++ i) {
            ll pro = 1, base = n - i; // 1e7，不怂 
            for(int j = 0 ; j <= DEG ; ++ j) {
                ll val = pro * res[i * (DEG + 1) + j][res[0].size() - 1] % mod;
                pro = pro * base % mod;
                if(i == 0) {
                    coef = (coef + val) % mod;
                }
            }
            break;
        }
        assert(coef);
        thecoefs[++ top] = -coef;
    }
    runinv(top);
    top = 0;
    for(int n = k + 15 ; n <= :: n ; ++ n) {
        ll s = 0, coef = 0;
        for(int i = 0 ; i <= L ; ++ i) {
            ll pro = 1, base = n - i; // 1e7，不怂 
            for(int j = 0 ; j <= DEG ; ++ j) {
                ll val = pro * res[i * (DEG + 1) + j][res[0].size() - 1] % mod;
                pro = pro * base % mod;
                if(i == 0) {
                    coef = (coef + val) % mod;
                } else {
                    val = val * f[n - i] % mod;
                    s = (s + val) % mod;
                }
            }
        }
        f[n] = s * thecoefs[++ top] % mod;
    }
    printf("%lld\n", (f[:: n] % mod + mod) % mod);
}
