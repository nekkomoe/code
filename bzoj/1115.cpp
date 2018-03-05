#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int T, a[1010];

int main() {
    scanf("%d", &T);
    while(T --) {
        int ans = 0;
        int n; scanf("%d", &n);
        for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
        for(int i = n ; i > 1 ; i -= 2) ans ^= a[i] - a[i - 1];
        if(n & 1) ans ^= a[1];
        puts(ans ? "TAK" : "NIE");
    }
}
