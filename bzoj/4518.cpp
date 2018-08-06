#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 3010;

int n, m, q[N];

ll s[N], f[N], g[N];

double slp(int i, int j) {
    return (double) (g[i] + s[i] * s[i] - g[j] - s[j] * s[j]) / (s[i] - s[j]);
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &s[i]);
        s[i] += s[i - 1];
        g[i] = s[i] * s[i];
    }
    for(int i = 1 ; i < m ; ++ i) {
        int l = 1, r = 1;
        q[1] = i;
        for(int j = i + 1 ; j <= n ; ++ j) {
            while(l < r && slp(q[l], q[l + 1]) < 2 * s[j]) ++ l;
            int t = q[l];
            f[j] = g[t] + (s[j] - s[t]) * (s[j] - s[t]);
            while(l < r && slp(q[r], q[r - 1]) > slp(q[r], j)) -- r;
            q[++ r] = j;
        }
        for(int i = 1 ; i <= n ; ++ i) g[i] = f[i];
    }
    printf("%lld\n", -s[n] * s[n] + m * f[n]);
}
