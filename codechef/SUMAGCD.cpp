#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, a[N], pre[N], sub[N];
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
void runprog() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }

    sort(a + 1, a + 1 + n);
    n = unique(a + 1, a + 1 + n) - a - 1;
    if(n == 1) {
        printf("%lld\n", 2ll * a[1]);
        return ;
    }

    for(int i = 1 ; i <= n ; ++ i) {
        pre[i] = gcd(pre[i - 1], a[i]);
    }
    sub[n + 1] = 0;
    for(int i = n ; i ; -- i) {
        sub[i] = gcd(sub[i + 1], a[i]);
    }
    ll ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        ans = max(ans, a[i] + gcd(pre[i - 1], sub[i + 1]));
    }
    printf("%lld\n", ans);
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
