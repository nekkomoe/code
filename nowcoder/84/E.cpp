#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
 
const int N = 100010;
 
typedef long long ll;
 
int n, p;
 
set<ll> ans, mp[2];
 
ll a[N], sum[N];
 
int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%lld", &a[i]), sum[i] = sum[i - 1] + a[i];
    mp[p].insert(a[n]);
    ans.insert(a[n]);
    for(int i = n - 1 ; i ; -- i) {
        p ^= 1;
        mp[p].clear();
        mp[p].insert(a[i]);
        ans.insert(a[i]);
        for(set<ll> :: iterator it = mp[p ^ 1].begin() ; it != mp[p ^ 1].end() ; ++ it) {
            mp[p].insert(a[i] | *it);
            ans.insert(a[i] | *it);
        }
    }
    printf("%lld\n", (ll) ans.size());
}
