#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, ans, a[N], val[N], S;
int vis[N], f[N];

int sol(int S) {
    if(!S) return 0;
    if(vis[S]) return f[S];
    f[S] = 0x3f3f3f3f;
    vis[S] = 1;
    for(int i = 1 ; i <= 15 ; ++ i) {
        if(S & (1 << i)) {
            for(int j = 1 ; j <= 15 ; ++ j) {
                if(i != j && (S & (1 << j))) {
                    int t = i ^ j;
                    if(S & (1 << t)) {
                        f[S] = min(f[S], sol(S ^ (1 << i) ^ (1 << j) ^ (1 << t)) + 2);
                    } else {
                        f[S] = min(f[S], sol(S ^ (1 << i) ^ (1 << j) ^ (1 << t)) + 1);
                    }
                }
            }
        }
    }
    return f[S];
}

int main() {
    scanf("%d", &n);
    for(int i = 1, u, v, w ; i < n ; ++ i) {
        scanf("%d%d%d", &u, &v, &w);
        a[u] ^= w;
        a[v] ^= w;
    }
    for(int i = 0 ; i < n ; ++ i) {
        ++ val[a[i]];
    }
    for(int i = 1 ; i <= 15 ; ++ i) {
        ans += val[i] / 2;
        if(val[i] % 2 == 1) {
            S ^= 1 << i;
        }
    }
    printf("%d\n", ans + sol(S));
}
