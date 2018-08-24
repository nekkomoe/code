#include "bits/stdc++.h"
using namespace std;
const int N = 1e6 + 10;
int n, ans;
char s[N];
int main() {
    scanf("%s", s + 1), n = strlen(s + 1);
    for(int i = 1 ; i <= n ; ++ i) s[i + n] = s[i]; n *= 2;
    for(int i = 1, mx = 0 ; i <= n ; ++ i) {
        ans = max(ans, mx = mx * (s[i] != s[i - 1]) + 1);
    }
    printf("%d\n", min(ans, n / 2));
}
