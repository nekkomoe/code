#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 10;
int n, cnt[30];
char s[N];
int main() {
    scanf("%d%s", &n, s + 1);
    for(int i = 1 ; i <= n ; ++ i) {
        ++ cnt[s[i] - 'a'];
    }
    int tot = 0;
    for(int i = 0 ; i < 26 ; ++ i) {
        tot += cnt[i] == 1;
    }
    if(tot == n && n != 1) {
        puts("No");
    } else {
        puts("Yes");
    }
}
