#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int K = 35, mod = 1e9 + 7, N = 1 << 18;
unordered_map<int, int> F[K];
int n, k, f[N][K];
int sol(int n, int k) {
    if(n < (1 << k)) return 0;
    if(k == 1) return n - 1;
    int &res = n - (1 << k) < N ? f[n - (1 << k)][k] : F[k][n];
    if(res) return res;
    for(int i = 2, j ; i <= n ; i = j + 1) {
        j = n / (n / i);
        if(n / i < (1 << (k - 1))) break;
        res = ((ll) res + (j - i + 1ll) * sol(n / i, k - 1)) % mod;
    }
    return res;
}
int main() {
    while(scanf("%d%d", &n, &k) == 2) {
        printf("%d\n", sol(n, k));
    }
}
