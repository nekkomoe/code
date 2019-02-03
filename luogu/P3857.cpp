#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 110;

int n, m, tot; char s[N];
ll a[N];

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%s", s + 1); ll x = 0;
        int len = strlen(s + 1);
        for(int j = 1 ; j <= len ; ++ j) {
            x = (x << 1) | (s[j] == 'O');
        }
        for(int j = 60 ; ~ j ; -- j) {
            if(x & (1ll << j)) {
                if(!a[j]) {
                    a[j] = x;
                    ++ tot;
                    break;
                }
                x ^= a[j];
            }
        }
    }
    printf("%lld\n", (1ll << tot) % 2008);
}
