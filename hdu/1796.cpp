#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, a[20], cnt[1020];
int m;

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    for(int i = 0 ; i < (1 << 10) ; ++ i) cnt[i] = cnt[i >> 1] + (i & 1);
    while(cin >> n >> m) {
        -- n;
        ll ans = 0;
        int tot = 0;
        for(int i = 1 ; i <= m ; ++ i) {
            int x; cin >> x;
            if(x) a[++ tot] = x;
        }
        m = tot;
        for(int s = 1 ; s < (1 << m) ; ++ s) {
            ll p = 1;
            for(int i = 1 ; i <= m ; ++ i)
                if((s >> (i - 1)) & 1)
                    p = p / gcd(p, a[i]) * a[i];
            ans += ((cnt[s] & 1) ? 1 : -1) * abs(n / p);
        }
        cout << ans << endl;
    }
}
