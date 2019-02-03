#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 110;

int n, cnt;
ll a[N], ans, mx;

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        ll x; scanf("%lld", &x);
        for(int j = 62 ; ~ j ; -- j) {
            if(x & (1ll << j)) {
                if(!a[j]) {
                    a[j] = x;
                    ++ cnt;
                    break;
                }
                x ^= a[j];
            }
        }
    }
    for(int j = 62 ; ~ j ; -- j) {
        if((mx ^ a[j]) > mx) {
            mx ^= a[j];
        }
    }
    ans += mx * (n - (-- cnt));
    for(int i = 0 ; i <= 62 ; ++ i) {
        if(a[i]) {
            for(int j = i - 1 ; ~ j ; -- j) {
                if(a[i] & (1ll << j)) {
                    a[i] ^= a[j];
                }
            }
        }
    }
    for(int i = 0 ; cnt && i <= 62 ; ++ i) {
        if(a[i]) {
            ans += mx ^ a[i];
            -- cnt;
        }
    }
    printf("%lld\n", ans);
}
