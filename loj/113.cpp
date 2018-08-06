// 线性基 贪心

#include <cstdio>

using namespace std;

typedef long long ll;

int n;

ll ans, a[60];

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        ll x;
        scanf("%lld", &x);
        for(int j = 60 ; ~ j ; -- j) {
            if((x >> j) & 1) {
                if(!a[j]) {
                    a[j] = x;
                    break;
                }
                x ^= a[j];
            }
        }
    }
    for(int i = 60 ; ~ i ; -- i) {
        if((ans ^ a[i]) > ans) ans ^= a[i];
    }
    printf("%lld\n", ans);
}