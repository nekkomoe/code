#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 1e6 + 10;

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

int n;
ll A, B, l[N], r[N];

vector<pair<ll, ll> > ln;
vector<ll> num;
ll a[int(5e6) + 10];

int main() {
    scanf("%d%lld%lld", &n, &A, &B);
    ll s = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld%lld", &l[i], &r[i]);
        s += r[i] - l[i] + 1;
    }
    ll g = __gcd(A, B + 1);
    if((__int128) A / g * B > (ll) (1e18)) {
        printf("%lld\n", s);
        return 0;
    }
    ll T = A / g * B;
    for(int i = 1 ; i <= n ; ++ i) {
        ll l = :: l[i], r = :: r[i];
        if(r - l + 1 >= T) {
            printf("%lld\n", T);
            return 0;
        }
        l %= T, r %= T;
        // printf("%lld, %lld\n", l, r);
        if(l <= r) {
            ln.emplace_back(l, r);
        } else {
            ln.emplace_back(0, r);
            ln.emplace_back(l, T - 1);
        }
    }
    for(auto t: ln) {
        for(ll j = t.first - 1 ; j <= t.first + 1 ; ++ j) {
            if(0 <= j && j < T) {
                num.emplace_back(j);
            }
        }
        for(ll j = t.second - 1 ; j <= t.second + 1 ; ++ j) {
            if(0 <= j && j < T) {
                num.emplace_back(j);
            }
        }
    }
    sort(num.begin(), num.end());
    num.erase(unique(num.begin(), num.end()), num.end());
    for(auto &t: ln) {
        // printf("[%lld, %lld]\n", t.first, t.second);
        t.first = lower_bound(num.begin(), num.end(), t.first) - num.begin() + 1;
        t.second = lower_bound(num.begin(), num.end(), t.second) - num.begin() + 1;
        a[t.first] ++;
        a[t.second + 1] --;
    }
    int lim = num.size();
    ll ans = 0;
    for(int i = 1 ; i <= lim ; ++ i) {
        a[i] += a[i - 1];
    }
    for(int i = 1 ; i <= lim ; ) {
        if(!a[i]) {
            ++ i;
            continue;
        }
        int j = i;
        while(j + 1 <= lim && a[j + 1]) {
            ++ j;
        }
        ans += num[j - 1] - num[i - 1] + 1;
        i = j + 1;
    }
    printf("%lld\n", ans);
}
