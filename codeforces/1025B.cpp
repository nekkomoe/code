#include "bits/stdc++.h"
using namespace std;
const int N = 1e6 + 10;
int a[N], b[N], n;

void f(int x) {
    if(x == 1) return ;
    for(int i = 2 ; i * i <= x ; ++ i) if(x % i == 0) return ;
    for(int i = 2 ; i <= n ; ++ i)
        if(a[i] % x && b[i] % x)
            return ;
    printf("%d\n", x);
    exit(0);
}

void sol(int x) {
    for(int i = 1 ; i * i <= x ; ++ i)
        if(x % i == 0)
            f(i), f(x / i);
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d%d", &a[i], &b[i]);
    sol(a[1]), sol(b[1]);
    puts("-1");
}
