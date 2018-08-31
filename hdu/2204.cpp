#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n;
const int N = 100;
int vis[N], p[N], tot;

ll calc(ll x) {
    return (long long) pow(n, 1.0 / x) - 1;
}

void sol() {
    ll ans = 1;
    for(int i = 1 ; i <= tot && calc(p[i]) ; ++ i) {
        ans += calc(p[i]);
        for(int j = i + 1 ; j <= tot && calc(p[i] * p[j]) ; ++ j) {
            ans -= calc(p[i] * p[j]);
            for(int k = j + 1 ; k <= tot && calc(p[i] * p[j] * p[k]) ; ++ k) {
                ans += calc(p[i] * p[j] * p[k]);
            }
        }
    }
    cout << ans << endl;
}

int main() {
    for(int i = 2 ; i < N ; ++ i) {
        if(!vis[i]) p[++ tot] = i;
        for(int j = 1 ; j <= tot && i * p[j] < N ; ++ j) {
            vis[i * p[j]] = 1;
            if(i % p[j] == 0) break;
        }
    }
    while(cin >> n) sol();
}
