#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 10;
int n, q, a[N], pre[N], sub[N];
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
void read(int &x) {
    char c = x = 0;
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
}
void sol() {
    read(n), read(q);
    for(int i = 1 ; i <= n ; ++ i) read(a[i]), pre[i] = sub[i] = a[i];
    pre[0] = sub[n + 1] = 0;
    for(int i = 2 ; i <= n ; ++ i) pre[i] = gcd(pre[i - 1], pre[i]);
    for(int i = n - 1 ; i >= 1 ; -- i) sub[i] = gcd(sub[i + 1], sub[i]);
    for(int i = 1, l, r ; i <= q ; ++ i) {
        read(l), read(r);
        printf("%d\n", gcd(pre[l - 1], sub[r + 1]));
    }
}
int main() {
    int T; read(T);
    while(T --) sol();
}

