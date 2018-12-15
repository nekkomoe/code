#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10, mod = 1e9 + 1;
int n, vis[N], num[N], cnt[1 << 21];
ll ans = 1, f[2][1 << 21];

void sol(int start) {
    int len = 0, height = 0;
    for(int i = start ; i <= n ; i *= 2) {
        ++ height;
        num[height] = 0;
        for(int j = i ; j <= n ; j *= 3) {
            vis[j] = 1;
            ++ num[height];
        }
        len = max(len, num[height]);
    }
    int p = 0;
    int mxs = 1 << len;
    for(int i = 0 ; i < mxs ; ++ i) f[p][i] = 0;
    f[p][0] = 1;
    for(int i = 1 ; i <= height ; ++ i) {
        p ^= 1;
        for(int i = 0 ; i < mxs ; ++ i) f[p][i] = 0;
        for(int s = 0 ; s < mxs ; ++ s) {
            if((s & (s << 1)) == 0 && cnt[s] <= num[i]) {
                for(int t = 0 ; t < mxs ; ++ t) {
                    if((t & (t << 1)) == 0 && cnt[t] <= num[i - 1]) {
                        if((s & t) == 0) {
                            (f[p][s] += f[p ^ 1][t]) %= mod;
                        }
                    }
                }
            }
        }
    }
    
    ll res = 0;
    for(int s = 0 ; s < mxs ; ++ s)
        (res += f[p][s]) %= mod;
        
    (ans *= res) %= mod;
}

int main() {
    for(int s = 0 ; s < (1 << 21) ; ++ s) {
        for(int i = 20 ; i ; -- i) {
            if((s >> (i - 1)) & 1) {
                cnt[s] = i;
                break;
            }
        }
    }
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        if(!vis[i]) {
            sol(i);
        }
    }
    printf("%lld\n", (ans % mod + mod) % mod);
}

