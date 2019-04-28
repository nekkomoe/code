#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
__int128 f[N], s[N];
ll x;

int main() {
    f[1] = f[2] = 1;
    s[1] = 1, s[2] = s[1] + f[2];
    scanf("%lld", &x);
    for(int i = 1 ; ; ++ i) {
        if(i > 2) {
            f[i] = s[i - 1] / 2;
            s[i] = s[i - 1] + f[i];
        }
        if(s[i] > x) {
            printf("%d\n", i);
            break;
        }
    }
}
