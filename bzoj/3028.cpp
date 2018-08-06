#include <bits/stdc++.h>
const int mod = 10007;
int n; char s[600];
int main() {
    scanf("%s", s + 1);
    for(int i = 1 ; s[i] ; ++ i)
        n = (n * 10 + s[i]-'0') % mod;
    printf("%d\n", n * (n + 1) % mod * (n + 2) % mod * 1668 % mod);
}
