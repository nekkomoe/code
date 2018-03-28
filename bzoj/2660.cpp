//dp

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int N = 90;

long long  f[N], n, p[N], tmp, dp[N][2];

int main() {
    f[1] = 1;
    f[2] = 2;
    for(int i = 3 ; i < N ; i ++) {
        f[i] = f[i - 1] + f[i - 2];
    }
    cin >> n;
    for(int i = N - 1 ; i ; i --) {
        if(n >= f[i]) {
            n -= f[i];
            p[++ tmp] = i;
        }
    }
    reverse(p + 1, p + 1 + tmp);
    dp[1][1] = 1;
    dp[1][0] = (p[1] - 1) / 2;
    for(int i = 2 ; i <= tmp ; i ++) {
        dp[i][1] = dp[i - 1][0] + dp[i - 1][1];
        dp[i][0] = dp[i - 1][1] * ((p[i] - p[i - 1] - 1) / 2) + dp[i - 1][0] * ((p[i] - p[i - 1]) / 2);
    }
    cout << (dp[tmp][0] + dp[tmp][1]) << endl;
}
