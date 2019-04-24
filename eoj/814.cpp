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

const int N = 5e5 + 10;

int notpri[N];

void init(int n) {
    notpri[1] = 1;
    for(int i = 2 ; i <= n ; ++ i) {
        if(!notpri[i]) {
            for(int j = i + i ; j <= n ; j += i) {
                notpri[j] = 1;
            }
        }
    }
}

vector<int> res;
int vis[N];
void pb(int x) {
    vis[x] = 1;
    res.push_back(x);
}

vector<int> getans() {
    int n; scanf("%d", &n);
    res.clear();
    if(n <= 11) {
        for(int i = 2 ; i <= n ; i += 2) {
            res.push_back(i);
        }
    } else {
        memset(vis, 0, sizeof vis);
        pb(2);
        for(int i = 4, j = 0 ; i <= n / 3 ; ++ i) {
            if(notpri[i]) continue;
            int x = 2 * i, y = 3 * i;
            if(j) swap(x, y);
            j ^= 1;
            vis[x] = vis[y] = 1;
            pb(x);
            for(int k = i ; k <= n ; k += i) {
                if(!vis[k]) {
                    pb(k);
                }
            }
            pb(y);
        }
        pb(6), pb(3);
        for(int i = 3 ; i <= n ; i += 3) {
            if(!vis[i] && i != 12) {
                pb(i);
            }
        }
        pb(12);
        for(int i = 2 ; i <= n ; i += 2) {
            if(!vis[i]) {
                pb(i);
            }
        }
    }
    return res;
}

int main() {
// #ifdef ONLINE_JUDGE
//     freopen("cycle.in", "r", stdin);
//     freopen("cycle.out", "w", stdout);
// #endif
    init(N - 1);
    int t; scanf("%d", &t);
    while(t --) {
        vector<int> res = getans();
        printf("%d\n", int(res.size()));
        for(int x: res) {
            printf("%d ", x);
        }
        puts("");
    }
}
