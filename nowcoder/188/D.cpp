#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 10000 + 10, mod = 2333;
int n; char s[N];
map<pair<int, int>, int> f[N];
 
int dfs(int pos, int j, int k) {
    if(pos == 0) {
        return j == 0 && k == 0;
    } else if(j < 0 || k < 0) {
        return 0;
    } else if(f[pos].find({j, k}) != f[pos].end()) {
        return f[pos][{j, k}];
    } else {
        int sig = s[pos] == '(' ? -1 : 1;
        return f[pos][{j, k}] = (1ll * dfs(pos - 1, j + sig, k) + dfs(pos - 1, j, k + sig)) % mod;
    }
}
 
int main() {
    scanf("%d%s", &n, s + 1);
    ll ans = dfs(n, 0, 0);
    ans = (ans % mod + mod) % mod;
    printf("%lld\n", ans);
}
