#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int T = 1e6, N = T + 10;

int n;

ll a[N], f[N], cnt[N]; 

int main() {
    ios :: sync_with_stdio();
    cin >> n;
    for(int i = 1 ; i <= n ; ++ i) cin >> a[i];
    
    
    ll sum = 0, ans;
    for(int i = 1 ; i <= n ; ++ i) sum += a[i], ++ cnt[a[i]]; ans = sum;
    
    for(int i = T ; i ; -- i) cnt[i] += cnt[i + 1];
    
    for(ll i = 1 ; i <= T ; ++ i) {
        for(ll j = i ; j <= T ; j += i) {
            f[i] += cnt[j] * (1 - i);
        }
    }
    
    for(int i = 1 ; i <= T ; ++ i) {
        ans = min(ans, sum + f[i]);
    }
    
    cout << ans << endl;
}

