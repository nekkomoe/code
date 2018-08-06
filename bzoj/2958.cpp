#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 1e6 + 10;

typedef long long ll;

const ll p = 1e9 + 7;

int n, k, b[N], w[N];

char s[N];

ll f[N][4][2];

/*
 * f[i][0(none)/1(only k black)/2(k black and k white)][B/W]
 * */

void sol() {
    f[0][0][0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        b[i] = b[i - 1] + (s[i] == 'B'), w[i] = w[i - 1] + (s[i] == 'W');
        if(s[i] == 'B' || s[i] == 'X') {
            f[i][2][0] = (f[i - 1][2][0] + f[i - 1][2][1]) % p;
            f[i][0][0] = (f[i - 1][0][0] + f[i - 1][0][1]) % p;
            f[i][1][0] = (f[i - 1][1][0] + f[i - 1][1][1]) % p;
            if(i >= k && w[i] - w[i - k] == 0 && s[i - k] != 'B') {
                f[i][0][0] -= f[i - k][0][i != k]; (f[i][0][0] += p) %= p;
                f[i][1][0] += f[i - k][0][i != k]; f[i][1][0] %= p;
            }
        }
        if(s[i] == 'W' || s[i] == 'X') {
            f[i][0][1] = (f[i - 1][0][0] + f[i - 1][0][1]) % p;
            f[i][1][1] = (f[i - 1][1][0] + f[i - 1][1][1]) % p;
            f[i][2][1] = (f[i - 1][2][0] + f[i - 1][2][1]) % p;
            if(i >= k && b[i] - b[i - k] == 0 && s[i - k] != 'W') {
                f[i][1][1] -= f[i - k][1][0]; (f[i][1][1] += p) %= p;
                f[i][2][1] += f[i - k][1][0]; f[i][2][1] %= p;
            }
        }
    }
}

int main() {
    scanf("%d%d%s", &n, &k, s + 1);
    sol();
    printf("%lld\n", (f[n][2][0] + f[n][2][1]) % p);
}
