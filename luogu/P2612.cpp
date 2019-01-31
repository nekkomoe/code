#pragma GCC optimize(2)
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
#define range [2][105][10005][3]
#define OFFSET 5000
int n, m, k; long double ld_f range;

#ifdef ONLINE_JUDGE
__float128 flt_f range;
#else
long double flt_f range;
#endif

template<typename T> void print(T x) {
    // cout << fixed << setprecision(k) << x << endl;
    printf("0.");
    for(int i = 1 ; i <= k ; ++ i) {
        x *= 10;
        printf("%d", int(x + (i == k) * 0.5));
        x -= int(x);
    }
}

template<typename T> void sol(T f range) {
    T ans = 0;
    int cur = 0;
    f[0][0][OFFSET][0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        cur ^= 1;
        memset(f[cur], 0, sizeof f[cur]);
        for(int j = 0 ; j <= i - 1 ; ++ j) {
            for(int k = 0 ; k <= 10000 ; ++ k) {
                for(int l = 0 ; l <= 2 ; ++ l) {
                    if(l != 2) {
                        // 可以放在两侧
                        if(k - i >= 0) {
                            f[cur][j + 1][k - i][l + 1] += f[!cur][j][k][l] * (2 - l);
                        }
                        if(j && k + i <= 10000) {
                            f[cur][j][k + i][l + 1] += f[!cur][j][k][l] * (2 - l);
                        }
                    }
                    if(j >= 2 && k + 2 * i <= 10000) {
                        // 可以合并两个块
                        f[cur][j - 1][k + 2 * i][l] += f[!cur][j][k][l] * (j - 1);
                    }
                    if(k - 2 * i >= 0) {
                        // 独自成为一个块
                        f[cur][j + 1][k - 2 * i][l] += f[!cur][j][k][l] * (j + 1 - l);
                    }
                    if(j) {
                        // 只与一个块相邻
                        f[cur][j][k][l] += f[!cur][j][k][l] * (2 * j - l);
                    }
                }
            }
        }
    }
    for(int i = OFFSET + m ; i <= 10000 ; ++ i) ans += f[cur][1][i][2];
    for(int i = 1 ; i <= n ; ++ i) ans /= i;
    print(ans);
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    if(k <= 8) {
        sol(ld_f);
    } else {
        sol(flt_f);
    }
}

