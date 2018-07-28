#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 10;
int n, k, a[N], vis[N];
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int main() {
    scanf("%d%d", &n, &k);
    int g = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        g = gcd(g, a[i]);
    }
    set<int> ans;
    for(long long i = 0, s = 0 ; i < k ; ++ i, s += g) ans.insert(s % k);
    printf("%d\n", ans.size());
    for(auto i: ans) printf("%d ", i);
}
