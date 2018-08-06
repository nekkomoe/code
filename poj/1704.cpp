#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int n, k, a[1010];

int main() {
    int T; scanf("%d", &T);
    while(T --) {
        scanf("%d", &n);
        for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
        sort(a + 1, a + 1 + n);
        int ans;
        if(n & 1) {
            ans = a[1] - 1;
            for(int i = 3 ; i <= n ; i += 2) ans ^= (a[i] - a[i - 1] - 1);
        } else {
            ans = a[2] - a[1] - 1;
            for(int i = 4 ; i <= n ; i += 2) ans ^= (a[i] - a[i - 1] - 1);
        }
        puts(ans ? "Georgia will win" : "Bob will win");
    }
}
