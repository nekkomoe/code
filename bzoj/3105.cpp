#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

ll a[110], ans;
int n, t[110];

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &t[i]);
    }
    sort(t + 1, t + 1 + n);
    for(int i = n ; i ; -- i) {
        int x = t[i], flag = 1;
        for(int j = 31 ; ~ j ; -- j) {
            if(x & (1 << j)) {
                if(!a[j]) {
                    a[j] = x;
                    flag = 0;
                    break;
                }
                x ^= a[j];
            }
        }
        if(flag) {
            ans += t[i];
        }
    }
    printf("%lld\n", ans);
}

