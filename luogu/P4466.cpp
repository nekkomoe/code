// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int T = 2e5, N = T + 10;

ll n, ans;

int mu[N], pri[N], tot, vis[N];

int main() {
    ios :: sync_with_stdio();
    cin >> n;
    mu[1] = 1;
    for(int i = 2 ; i <= T ; ++ i) {
        if(!vis[i]) {
            pri[++ tot] = i;
            mu[i] = -1;
        }
        for(int j = 1 ; j <= tot && i * pri[j] <= T ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) break;
            mu[i * pri[j]] = -mu[i];
        }
    }
    ll T = ceil(sqrt(n));
    for(ll d = 1 ; d <= T ; ++ d) {
        if(mu[d]) {
            for(ll i = 2 ; i <= T / d ; ++ i) {
                ll up = n / (d * d * i);
                for(ll j = i + 1, nxtj ; j <= up && j <= 2 * i - 1 ; j = nxtj + 1) {
                    nxtj = min(2 * i - 1, up / (up / j));
                    ans += n / (d * d * i * j) * mu[d] * (nxtj - j + 1);
                }
            }
        }
    }
    cout << ans << endl;
}

