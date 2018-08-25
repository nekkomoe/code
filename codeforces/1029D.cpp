#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;

int n, k, a[N];

// map<int, int> cnt[11];

int val[11][N], fafa[11][N];

int getlen(int x) {
    // while(x == 0);
    int r = 0;
    while(x) x /= 10, ++ r;
    return r;
}

void read(int &x) {
    char c = x = 0;
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

int main() {
    read(n), read(k);

    long long ans = 0;
    for(int i = 1 ; i <= n ; ++ i) read(a[i]);
    for(int i = 0, t = 1 ; i <= 10 ; ++ i, t = 1ll * t * 10 % k) {
        for(int j = 1 ; j <= n ; ++ j) {
            val[i][j] = 1ll * a[j] * t % k;
            fafa[i][j] = 1ll * a[j] * t % k;
        }
        sort(val[i] + 1, val[i] + 1 + n);
    }

    for(int i = 1 ; i <= n ; ++ i) {
        int len = getlen(a[i]);
        int x = ((1ll * -a[i] % k) + k) % k;
        if(val[len][1] <= x && x <= val[len][n]) {
            int* l = lower_bound(val[len] + 1, val[len] + 1 + n, x);
            if(*l == x) {
                int* r = upper_bound(val[len] + 1, val[len] + 1 + n, x);
                -- r;
                ans += r - l + 1;
            }
            if(fafa[len][i] == x) -- ans;
        }
    }

    printf("%lld\n", ans);
}

// (ai * 10^|aj| + aj) % k = 0
