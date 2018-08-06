#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int n, a[1010];

int main() {
    while( scanf("%d", &n) == 1 && n) {
        int ans = 0, sum = 0;
        for( int i = 1 ; i <= n ; ++ i ) scanf("%d", &a[i]), sum ^= a[i];
        for( int i = 1 ; i <= n ; ++ i ) if( (sum ^ a[i]) < a[i] ) ++ ans;
        printf("%d\n", ans);
    }
}
