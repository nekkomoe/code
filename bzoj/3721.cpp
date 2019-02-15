#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
int n, m;
ll sum[N], a[N];
ll pre_min_odd[N];
ll pre_min_even[N];
ll sub_max_odd[N];
ll sub_max_even[N];
 
const ll inf = 0x3f3f3f3f3f3f3f3fll;
 
int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &a[i]);
    }
    sort(a + 1, a + 1 + n, greater<int> ());
     
    pre_min_odd[0] = inf;
    pre_min_even[0] = inf;
    for(int i = 1 ; i <= n ; ++ i) {
        sum[i] = sum[i - 1] + a[i];
        if(a[i] & 1) {
            pre_min_odd[i] = min(pre_min_odd[i - 1], a[i]);
            pre_min_even[i] = pre_min_even[i - 1];
        } else {
            pre_min_odd[i] = pre_min_odd[i - 1];
            pre_min_even[i] = min(pre_min_even[i - 1], a[i]);
        }
    }
    sub_max_odd[n + 1] = -inf;
    sub_max_even[n + 1] = -inf;
    for(int i = n ; i ; -- i) {
        if(a[i] & 1) {
            sub_max_odd[i] = max(sub_max_odd[i + 1], a[i]);
            sub_max_even[i] = sub_max_even[i + 1]; 
        } else {
            sub_max_odd[i] = sub_max_odd[i + 1];
            sub_max_even[i] = max(sub_max_even[i + 1], a[i]); 
        }
    }
    scanf("%d", &m);
    while(m --) {
        int k; scanf("%d", &k);
        if(sum[k] & 1) {
            printf("%lld\n", sum[k]);
        } else {
            ll ans = -1;
            if(pre_min_odd[k] != inf && sub_max_even[k + 1] != -inf) ans = max(ans, sum[k] - pre_min_odd[k] + sub_max_even[k + 1]);
            if(pre_min_even[k] != inf && sub_max_odd[k + 1] != -inf) ans = max(ans, sum[k] - pre_min_even[k] + sub_max_odd[k + 1]);
            printf("%lld\n", ans); 
        }
    }
}
