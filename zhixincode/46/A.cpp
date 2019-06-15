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

char str[int(2e5) + 10];

int main() {
    scanf("%s", str + 1);
    map<int, int> cnt;
    for(int i = 1 ; str[i] ; ++ i) {
        ++ cnt[str[i] - '0'];
    }
   printf("%d\n", min(cnt[1] / 3, min(cnt[4] / 2, cnt[5]))); 
}
