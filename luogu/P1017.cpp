#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 
int n, r;
char str[100] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void f() {
    if(!n) return ;
    int x = n % r;
    n /= r;
    if(x < 0) {
        x -= r;
        ++ n;
    }
    f();
    putchar(str[x]);
}

int main() {
    scanf("%d%d", &n, &r);
    printf("%d=", n);
    f();
    printf("(base%d)\n", r);
} 
