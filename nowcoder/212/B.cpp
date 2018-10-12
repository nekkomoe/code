#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1010;
 
int n, m, k, a[N][N];
 
ll sum[N];
 
int main() {
    scanf("%d%d%d", &n, &m, &k);
    ll ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j)
            scanf("%d", &a[i][j]);
        sort(a[i] + 1, a[i] + 1 + m, greater<int> ());
        for(int j = 1 ; j <= m ; ++ j) sum[i] += a[i][j];
        ans += sum[i];
    }
    multiset<ll> s;
    if(k == n * m) {
        cout << ans << endl;
        exit(0);
    }
    for(int i = 1 ; i <= n ; ++ i) s.insert(sum[i]);
    for(int i = 1 ; i <= n ; ++ i) {
        s.erase(s.find(sum[i]));
        int lim = k % m;
        ll sss = 0;
        for(int j = 1 ; j <= lim ; ++ j) {
            sss += a[i][j];
        }
        int tot = k / m, cnt = 0;
        for(multiset<ll> :: iterator it = s.begin() ; it != s.end() ; ++ it) {
            if(++ cnt > tot) break;
            sss += *it;
        }
        s.insert(sum[i]);
        ans = min(ans, sss);
    }
    printf("%lld", ans);
}
