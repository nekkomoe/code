#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, k, f[2010][30], m, q[2010];

int dfs(int i, int j, int pi) {
    if(!j) return pi == n;
    for(-- j ; i + j <= m ; ++ i) {
        if(f[i][j] < 0) return 0;
        if((ll) f[i][j] * pi > n) return 0;
        if(dfs(i + 1, j, pi * q[i])) return 1;
    }
    return 0;
}

void sol() {
    scanf("%d%d", &n, &k);
    m = 0;
    for(int i = 1 ; i * i <= n ; ++ i) {
        if(n % i == 0) {
            q[++ m] = i;
            if(i * i < n) q[++ m] = n / i;
        }
    }
    sort(q + 1, q + 1 + m);
    for(int i = 1 ; i <= m ; ++ i) {
        ll t = 1;
        for(int j = 0 ; j < k && i + j <= m ; ++ j) {
            if(t > 0 && (t *= q[i + j]) > n) t = -1;
            f[i][j] = t;
        }
    }
    puts(dfs(1, k, 1) ? "TAK" : "NIE");
}

int main() {
    int T; scanf("%d", &T);
    while(T --) sol();
}
