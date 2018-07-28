#include "bits/stdc++.h"
using namespace std;
int n, k;
int main() {
    scanf("%d%d", &n, &k), -- k;
    int l = 1, r = n, flag = 1;
    while(l <= r) {
        if(flag) printf("%d ", l ++);
        else printf("%d ", r --);
        if(k) -- k, flag ^= 1;
    }
}

