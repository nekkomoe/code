#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 1e5 + 10;
 
typedef long long ll;
 
ll sum[N], f[2][N];
 
int n, k, tp, to[210][N], q[N];
 
double slp(int x, int y) {
    if(sum[x] == sum[y]) return -1e18;
    return (double) (sum[x] * sum[x] - sum[y] * sum[y] - f[tp ^ 1][x] + f[tp ^ 1][y]) / (double) (sum[x] - sum[y]);
}
 
int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &sum[i]);
        sum[i] += sum[i - 1];
    }
    for(int p = 1 ; p <= k ; ++ p) {
        int l = 0, r = 0; tp ^= 1;
        for(int i = 1 ; i <= n ; ++ i) {
            while(l < r && slp(q[l], q[l + 1]) <= sum[i]) ++ l;
            f[tp][i] = f[tp ^ 1][q[l]] + sum[q[l]] * (sum[i] - sum[q[l]]);
            to[p][i] = q[l];
            while(l < r && slp(q[r - 1], q[r]) >= slp(q[r], i)) -- r;
            q[++ r] = i;
        }
    }
    printf("%lld\n", f[tp][n]);
    // int i = n; for(int j = k ; j >= 1 ; -- j) i = to[j][i], printf("%d ", i);
}
