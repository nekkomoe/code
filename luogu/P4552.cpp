#include <bits/stdc++.h>

using namespace std;

const int N = 5e4 + 10;

int a[(int) 1e5 + 10], n;

int main() {
    scanf("%d", &n); for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
    long long x = 0, y = 0;
    for(int i = 2 ; i <= n ; ++ i) {
        if(a[i] > a[i - 1]) x += a[i] - a[i - 1];
        else y += a[i - 1] - a[i];
    }
    printf("%lld\n%lld\n", max(x, y), abs(x - y) + 1);
}

