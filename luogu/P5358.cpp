// luogu-judger-enable-o2
#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 10, mod = 1e7 + 19;
typedef long long ll;
int n, q;

struct QUERY {
    int op, id, val;
} nek[N];
int rev[N];
vector<int> num;

int coef_a[N], coef_b[N];

ll x, y, S, a[N]; // (a[i] + x) * y

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

int clk, st0, clk_a[N];

ll runprog(int op, int id, ll val) {

    // printf("(%lld, %lld)\n", x, y);

    val = (val % mod + mod) % mod;
    ++ clk;
    if(id) {
        // printf("id = %d\n", id);
        if(clk_a[id] < st0) {
            a[id] = 0;
        }
        clk_a[id] = clk;
    }
    if(op == 1) {
        // a[id] = val
        S = (S - ((a[id] + x) % mod * y % mod) % mod) % mod;
        a[id] = (val * pw(y, mod - 2) % mod - x) % mod;
        S = (S + val) % mod;
    } else if(op == 2) {
        // += val
        S = (S + n * val % mod) % mod;
        val = val * pw(y, mod - 2) % mod;
        x = (x + val) % mod;
    } else if(op == 3) {
        // *= val
        if(val == 0) {
            st0 = clk;
            x = 0, y = 1;
        } else {
            y = y * val % mod;
        }
        S = S * val % mod;
    } else if(op == 4) {
        // = val
        st0 = clk;
        x = val, y = 1;
        S = n * val % mod;
    } else if(op == 5) {
        ll ans = (a[id] + x) % mod * y % mod;
        // printf("%lld\n", (ans + mod) % mod);
        return ans;
    } else {
        // printf("%lld\n", (S + mod) % mod);
        return S;
    }
    return 0;
}

int main() {
    x = 0, y = 1;
    scanf("%d%d", &n, &q);
    for(int i = 1 ; i <= q ; ++ i) {
        int op = 0, id = 0, val = 0;
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d%d", &id, &val);
        } else if(op == 2) {
            scanf("%d", &val);
        } else if(op == 3) {
            scanf("%d", &val);
        } else if(op == 4) {
            scanf("%d", &val);
        } else if(op == 5) {
            scanf("%d", &id);
        } else {
            // pass
        }
        nek[i] = (QUERY) { op, id, val };
        if(id) {
            num.push_back(id);
        }
    }
    sort(num.begin(), num.end());
    num.erase(unique(num.begin(), num.end()), num.end());
    for(int i = 1 ; i <= q ; ++ i) {
        int id = nek[i].id;
        if(id) {
            rev[i] = lower_bound(num.begin(), num.end(), id) - num.begin() + 1;
        }
    }
    int t; scanf("%d", &t);
    for(int i = 1 ; i <= t ; ++ i) {
        scanf("%d%d", &coef_a[i], &coef_b[i]);
    }
    ll ans = 0;
    for(int i = 1 ; i <= t ; ++ i) {
        for(int j = 1 ; j <= q ; ++ j) {
            int os = (coef_a[i] + (ll) j * coef_b[i]) % q + 1;
            // printf("cf: %d %d\n", coef_a[i], coef_b[i]);
            // printf("os = %d\n", os);
            ll res = runprog(nek[os].op, rev[os], nek[os].val);
            ans += res;
            ans %= mod;
            // printf("%lld\n", res);
        }
    }
    printf("%lld\n", (ans + mod) % mod);
}


/*
// maker.cpp

#include "bits/stdc++.h"
using namespace std;

int main() {
    srand((unsigned long long) new char);
    int n = 3, q = n, t = 1;
    int VAL = 3;

    n = 1e9, q = 1e5, VAL = 1e9;
    t = 100;

    printf("%d %d\n", n, q);
    while(q --) {

//    1 i VAL ：将 a_i 赋值为给定整数 valval；
//    2 VAL ：将所有元素同时加上 valval；
//    3 VAL ：将所有元素同时乘上 valval；
//    4 VAL ：将所有元素同时赋值为 valval；
//    5 i ：询问第 i 个元素 a_i 现在的值是多少；
//    6 ：询问现在所有元素的和。
        int op = rand() % 6 + 1;
        if(op == 1) {
            printf("1 %d %d\n", rand() % n + 1, rand() % VAL);
        } else if(op == 2) {
            printf("2 %d\n", rand() % VAL);
        } else if(op == 3) {
            printf("3 %d\n", rand() % VAL);
        } else if(op == 4) {
            printf("4 %d\n", rand() % VAL);
        } else if(op == 5) {
            printf("5 %d\n", rand() % n + 1);
        } else if(op == 6) {
            printf("6\n");
        }
    }

    printf("%d\n", t);
    for(int i = 1 ; i <= t ; ++ i) {
        printf("%d %d\n", rand() % int(1e9), rand() % int(1e9));
    }
}
*/

/*
// force.cpp
#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 10, mod = 1e7 + 19;
typedef long long ll;
int n, q;

struct QUERY {
    int op, id, val;
} nek[N];
int rev[N];
vector<int> num;

int coef_a[N], coef_b[N];

ll x, y, S, a[N]; // (a[i] + x) * y

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

int clk, st0, clk_a[N];

ll runprog(int op, int id, ll val) {

    val = (val % mod + mod) % mod;
    
    if(op == 1) {
        // a[id] = val
        a[id] = val;
    } else if(op == 2) {
        // += val
        for(int i = 1 ; i <= n ; ++ i) {
            a[i] = (a[i] + val) % mod;
        }
    } else if(op == 3) {
        // *= val
        for(int i = 1 ; i <= n ; ++ i) {
            a[i] = (a[i] * val) % mod;
        }
    } else if(op == 4) {
        // = val
        for(int i = 1 ; i <= n ; ++ i) {
            a[i] = val;
        }
    } else if(op == 5) {
        return a[id];
    } else {
        ll S = 0;
        for(int i = 1 ; i <= n ; ++ i) {
            S = (S + a[i]) % mod;
        }
        return S;
    }
    return 0;
}

int main() {
    x = 0, y = 1;
    scanf("%d%d", &n, &q);
    for(int i = 1 ; i <= q ; ++ i) {
        int op = 0, id = 0, val = 0;
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d%d", &id, &val);
        } else if(op == 2) {
            scanf("%d", &val);
        } else if(op == 3) {
            scanf("%d", &val);
        } else if(op == 4) {
            scanf("%d", &val);
        } else if(op == 5) {
            scanf("%d", &id);
        } else {
            // pass
        }
        nek[i] = (QUERY) { op, id, val };
        if(id) {
            num.push_back(id);
        }
    }
    sort(num.begin(), num.end());
    num.erase(unique(num.begin(), num.end()), num.end());
    for(int i = 1 ; i <= q ; ++ i) {
        int id = nek[i].id;
        if(id) {
            rev[i] = lower_bound(num.begin(), num.end(), id) - num.begin() + 1;
        }
    }
    int t; scanf("%d", &t);
    for(int i = 1 ; i <= t ; ++ i) {
        scanf("%d%d", &coef_a[i], &coef_b[i]);
    }
    ll ans = 0;
    for(int i = 1 ; i <= t ; ++ i) {
        for(int j = 1 ; j <= q ; ++ j) {
            int os = (coef_a[i] + (ll) j * coef_b[i]) % q + 1;
            ll res = runprog(nek[os].op, nek[os].id, nek[os].val);
            ans += res;
            ans %= mod;
            // printf("%lld\n", res);
        }
    }
    printf("%lld\n", (ans + mod) % mod);
}
*/
