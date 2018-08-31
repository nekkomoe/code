%:pragma GCC optimize(2)
%:pragma GCC optimize(3)
%:pragma GCC optimize("Ofast")
%:pragma GCC optimize("inline")
%:pragma GCC optimize("-fgcse")
%:pragma GCC optimize("-fgcse-lm")
%:pragma GCC optimize("-fipa-sra")
%:pragma GCC optimize("-ftree-pre")
%:pragma GCC optimize("-ftree-vrp")
%:pragma GCC optimize("-fpeephole2")
%:pragma GCC optimize("-ffast-math")
%:pragma GCC optimize("-fsched-spec")
%:pragma GCC optimize("unroll-loops")
%:pragma GCC optimize("-falign-jumps")
%:pragma GCC optimize("-falign-loops")
%:pragma GCC optimize("-falign-labels")
%:pragma GCC optimize("-fdevirtualize")
%:pragma GCC optimize("-fcaller-saves")
%:pragma GCC optimize("-fcrossjumping")
%:pragma GCC optimize("-fthread-jumps")
%:pragma GCC optimize("-funroll-loops")
%:pragma GCC optimize("-fwhole-program")
%:pragma GCC optimize("-freorder-blocks")
%:pragma GCC optimize("-fschedule-insns")
%:pragma GCC optimize("inline-functions")
%:pragma GCC optimize("-ftree-tail-merge")
%:pragma GCC optimize("-fschedule-insns2")
%:pragma GCC optimize("-fstrict-aliasing")
%:pragma GCC optimize("-fstrict-overflow")
%:pragma GCC optimize("-falign-functions")
%:pragma GCC optimize("-fcse-skip-blocks")
%:pragma GCC optimize("-fcse-follow-jumps")
%:pragma GCC optimize("-fsched-interblock")
%:pragma GCC optimize("-fpartial-inlining")
%:pragma GCC optimize("no-stack-protector")
%:pragma GCC optimize("-freorder-functions")
%:pragma GCC optimize("-findirect-inlining")
%:pragma GCC optimize("-fhoist-adjacent-loads")
%:pragma GCC optimize("-frerun-cse-after-loop")
%:pragma GCC optimize("inline-small-functions")
%:pragma GCC optimize("-finline-small-functions")
%:pragma GCC optimize("-ftree-switch-conversion")
%:pragma GCC optimize("-foptimize-sibling-calls")
%:pragma GCC optimize("-fexpensive-optimizations")
%:pragma GCC optimize("-funsafe-loop-optimizations")
%:pragma GCC optimize("inline-functions-called-once")
%:pragma GCC optimize("-fdelete-null-pointer-checks")

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 4e5 + 10;
 
int vis[N], prime[N], tot, f[N], sz;

ll get(int n, int p) {
    // [1, n]
    if(n <= 0) return 0;
    ll res = 0;
    for(int s = 0 ; s < (1 << sz) ; ++ s) {
        int cnt = 0, lcm = 1;
        for(int i = 1 ; i <= sz ; ++ i) {
            if((s >> (i - 1)) & 1) {
                lcm = lcm / __gcd(lcm, f[i]) * f[i];
                ++ cnt;
            }
        }
        ll x = n / lcm;
        res += (cnt & 1 ? -1 : 1) * (1 + x) * x / 2 * lcm;
    }
    return res;
}

struct Q { int x, y; } ch[N];

void sol() {
    int n, m;
    scanf("%d%d", &n, &m);
    int cnt = 0;
    while(m --) {
        int op, x, y, p, c;
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d%d%d", &x, &y, &p);
            sz = 0;
            for(int i = 1 ; i <= tot && prime[i] <= p ; ++ i)
                if(p % prime[i] == 0)
                    f[++ sz] = prime[i];
            ll S = get(y, p) - get(x - 1, p);
            for(int i = 1 ; i <= cnt ; ++ i) {
                int pos = ch[i].x, val = ch[i].y;
                if(x <= pos && pos <= y) {
                    if(__gcd(pos, p) == 1) S -= pos;
                    if(__gcd(val, p) == 1) S += val;
                }
            }
            printf("%lld\n", S);
        } else {
            scanf("%d%d", &x, &c);
            bool flag = 1;
            for(int i = 1 ; i <= cnt ; ++ i)
                if(ch[i].x == x) {
                    ch[i].y = c;
                    flag = 0;
                    break;
                }
            if(flag) ch[++ cnt] = (Q) { x, c };
        }
    }
}

int main() {
    for(int i = 2 ; i < N ; ++ i) {
        if(!vis[i]) prime[++ tot] = i;
        for(int j = 1 ; j <= tot && prime[j] * i < N ; ++ j) {
            vis[i * prime[j]] = 1;
            if(i % prime[j] == 0) break;
        }
    }
    int T; scanf("%d", &T);
    while(T --) sol(); 
}
