#pragma GCC optimize(2)
// #pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
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

#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 3e4 + 10;

ll ans;
int inpn;
ll L[N];
ll l[N], p[N], c[N];
int m, n;
ll a[N], b[N];

ll sum[N], nek[N], ALLU;
ll get_le(int n) {
    ll res = ALLU;
    for(int i = 1 ; i <= n ; ++ i) {
        sum[i] = sum[i - 1] + nek[i];
    }
    for(int i = 1 ; i < n ; ++ i) {
        if((n - i) % 2) {
            ll s = sum[i] * nek[n];
            for(int j = i + 1, k = n - 1 ; j < k ; ++ j, -- k) {
                s += nek[j] * nek[k];
            }
            res = min(res, s);
        }
    }
    return res;
}

ll f[N], sl[N], sp[N];

int main() {
// #ifdef ONLINE_JUDGE
//     freopen("graph.in", "r", stdin);
//     freopen("graph.out", "w", stdout);
// #endif
    scanf("%d", &inpn);
    for(int i = 1 ; i <= inpn ; ++ i) {
        scanf("%lld", &L[i]);
        // assert(abs(L[i]) <= int(1e7));
        if(i > 1) {
            ALLU += L[i] * L[1];
        }
    }
    ans = 1ll << 62;
    sort(L + 1, L + 1 + inpn);

    for(int i = 1 ; i <= inpn ; ++ i) {
        if(L[i] < 0) {
            l[++ m] = L[i]; 
            sl[m] = sl[m - 1] + L[i];
        } else {
            p[++ n] = L[i];
            sp[n] = sp[n - 1] + L[i];
        }
    }

    if(n == 0) {
        for(int i = 1 ; i <= m ; ++ i) {
            nek[i] = l[i];
        }
        ans = min(ans, get_le(m));
    } else if(m == 0) {
        for(int i = 1 ; i <= n ; ++ i) {
            nek[i] = p[n - i + 1];
        }
        ans = min(ans, get_le(n));
    } else {
        for(int i = 1 ; i < m ; ++ i) {
            if((m - i) % 2) {
                for(int j = i + 1, k = m - 1 ; j < k ; ++ j, -- k) {
                    f[m - i - 1] += l[j] * l[k];
                }
            }
        }
        for(int i = max(n - m + 1, 1) ; i <= n ; ++ i) {
            ll res = 1ll << 62;
            if(m - (n - i) - 1 >= 2) {
                for(int j = 1 ; j < m - (n - i) - 1 ; ++ j) {
                    if((m - (n - i) - 1 - j) % 2) {
                        res = min(res,
    (sl[j + n - i + 1] - sl[n - i + 1]) * l[m] + f[m - (n - i) - 1 - j - 1]
                        );
                    }
                }
            }
            if(m - (n - i) - 1 == 1) {
                res = l[m] * l[m - 1];
            } else if(m - (n - i) - 1 == 0) {
                res = 0;
            }
            res += (sp[n] - sp[n - i]) * l[1];
            for(int j = 1 ; j <= n - i ; ++ j) {
                res += l[j + 1] * p[n - i - j + 1];
            }
            ans = min(ans, res);
        }
    }

    printf("%lld\n", ans);
}
