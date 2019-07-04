#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int n, p;
ll h[N], t[N];
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % p) {
        if(b & 1) {
            r = r * a % p;
        }
    }
    return r;
}

int main() {
    ll pw26 = 1;
    scanf("%d%d", &n, &p);
    for(int i = 0 ; i < n ; ++ i) {
        scanf("%lld", &h[i]);
        pw26 = pw26 * 26 % p;
    }
    for(int i = 0 ; i < n ; ++ i) {
        ll tarval = ((h[(i + 1) % n] - 26 * h[i] % p) % p + p) % p;
        int flag = 0;
        for(t[i] = 0 ; t[i] < 26 ; ++ t[i]) {
            if((t[i] * (1 - pw26) % p + p) % p == tarval) {
                flag = 1;
                break;
            }
        }
        if(!flag) {
            puts("QwQ");
            return 0;
        }
    }
    if(pw26 == 1) {
        stack<int> sta;
        ll x = h[0];
        for(int i = 0 ; i < n ; ++ i) {
            sta.push(x % 26);
            x = (x - x % 26) * pw(26, p - 2) % p;
        }
        while(sta.size()) {
            putchar(sta.top() + 'a');
            sta.pop();
        }
    } else {
        for(int i = 0 ; i < n ; ++ i) {
            putchar(t[i] + 'a');
        }
    }
}
