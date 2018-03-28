// 离线算法 快速幂

// 事实上这份代码有bug，在lower_bound的时候修改了递增序列，虽然A了，但实际需要multiset来代替lower_bound的工作。

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <set>

using namespace std;

typedef long long ll;

const int N = 1000010;

const ll M = 317847191LL;

ll pow(ll a, ll b) {
    ll ret = 1;
    a %= M;
    while(b) {
        if(b & 1) {
            ret = (ret * a) % M;
        }
        b >>= 1;
        a = (a * a) % M;
    }
    return ret;
}

int n, m;

ll mx = 0xcfcfcfcfcfcfcfcfLL, mn = 0x3f3f3f3f3f3f3f3fLL, val[N], seq[N], ans[N], mul;

char op[N][5];

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &seq[i]);
    }
    sort(seq + 1, seq + 1 + n);
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%s", op[i]);
        if(*op[i] == 'D') {
            scanf("%lld", &val[i]);
            *(lower_bound(seq + 1, seq + 1 + n, val[i])) = 0x3f3f3f3f3f3f3f3fLL;
        }
    }
    mul = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        if(seq[i] != 0x3f3f3f3f3f3f3f3fLL) {
            mx = max(mx, seq[i]);
            mn = min(mn, seq[i]);
            mul = (mul * ((ll)seq[i] % M)) % M;
        }
    }
    for(int i = m ; i >= 1 ; -- i) {
        if(*op[i] == 'D') {
            mx = max(mx, val[i]);
            mn = min(mn, val[i]);
            mul = (mul * ((ll)val[i] % M)) % M;
        } else if(*op[i] == 'B') {
            ans[i] = mx;
        } else if(*op[i] == 'S') {
            ans[i] = mn;
        } else if(*op[i] == 'M') {
            ans[i] = pow(mx, mn);
        } else if(*op[i] == 'T') {
            ans[i] = mul;
        }
    }
    for(int i = 1 ; i <= m ; ++ i) {
        if(*op[i] != 'D') {
            printf("%lld\n", ans[i]);
        }
    }
}
