#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const int mod = 1e9 + 7, N = 1e5 + 10;
 
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
 
int n, a[N];
 
int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }
    sort(a + 1, a + 1 + n);
    deque<int> q;
    for(int i = n ; i >= 1 ; -- i) {
        if(i & 1) {
            q.push_back(a[i]);
        } else {
            q.push_front(a[i]);
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        a[i] = q.front();
        q.pop_front();
    }
    a[0] = a[n], a[n + 1] = a[1];
    for(int i = 1 ; i <= n ; ++ i) {
        if(a[i] >= a[i - 1] + a[i + 1]) {
            puts("NO");
            return 0;
        }
    }
    puts("YES");
    for(int i = 1 ; i <= n ; ++ i) {
        printf("%d ", a[i]);
    }
}
