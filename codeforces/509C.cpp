#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
int n, dig[5000], len;
void nxt(int d) {
    for(int i = 1 ; d ; ++ i) {
        len = max(len, i);
        while(d && dig[i] < 9) -- d, ++ dig[i];
    }
}
int main() {
    scanf("%d", &n);
    for(int i = 1, last = 0, x, d ; i <= n ; ++ i) {
        scanf("%d", &x), d = x - last, last = x;
        if(d > 0) nxt(d);
        else {
            for(int i = 1 ; ; ++ i) {
                len = max(len, i);
                if(d > 0 && dig[i] < 9) {
                    -- d, ++ dig[i];
                    nxt(d);
                    break;
                }
                d += dig[i], dig[i] = 0;
            }
        }
        for(int i = len ; i ; -- i) printf("%d", dig[i]);
        puts("");
    }
}
