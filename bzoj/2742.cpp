#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 110, mod = 1e9 + 7;
int n, a[N];

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

ll calc(ll p, ll q) {
    ll x = p * pw(q, mod - 2) % mod, pro = 1, res = 0;
    for(int i = 0 ; i <= n ; ++ i) {
        res = (res + pro * a[i] % mod) % mod;
        pro = pro * x % mod;
    }
    return (res + mod) % mod == 0;
}

vector<int> split(int x) {
    x = abs(x);
    vector<int> res;
    for(int i = 1 ; i * i <= x ; ++ i)
        if(x % i == 0) {
            res.push_back(i);
            if(i != x / i) res.push_back(x / i);
        }
    return res;
}

int gcd(int a, int b) {
    return b ? gcd(b, a % b ) : a;
}

struct T { ll p, q; };
vector<T> ans;
bool cmp(T a, T b) {
    return a.p * b.q < a.q * b.p;
}
bool operator == (T a, T b) {
    return a.p == b.p && a.q == b.q;
}

int main() {
    scanf("%d", &n);
    for(int i = 0 ; i <= n ; ++ i) scanf("%d", &a[i]);
    int pos = 0; while(a[pos] == 0) ++ pos;
    vector<int> P = split(a[pos]),
                Q = split(a[n]);
    for(int i = 0 ; i < P.size() ; ++ i) {
        for(int j = 0 ; j < Q.size() ; ++ j) {
            int p = P[i], q = Q[j];
            if(gcd(p, q) == 1) {
                if(calc(p, q)) ans.push_back((T) { p, q });
                if(calc(-p, q)) ans.push_back((T) { -p, q });
            }
        }
    } 
    if(calc(0, 1)) ans.push_back((T) { 0, 1 });
    sort(ans.begin(), ans.end(), cmp);
    printf("%d\n", (int) ans.size());
    for(int i = 0 ; i < ans.size() ; ++ i) {
        ll p = ans[i].p, q = ans[i].q;
        if(q == 1) printf("%lld\n", p);
        else printf("%lld/%lld\n", p, q);
    }
}

