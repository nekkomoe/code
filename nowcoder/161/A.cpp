#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
int lst[26], ans;
char s[N];
int main() {
    scanf("%s", s + 1);
    ans = strlen(s + 1);
    for(int i = 1 ; s[i] ; ++ i) {
        bool flag = 1;
        lst[s[i] - 'a'] = i;
        int mn = i - lst[0] + 1;
        for(int j = 0 ; j < 26 ; ++ j) {
            if(!lst[j]) flag = 0;
            mn = max(mn, i - lst[j] + 1);
        }
        if(flag) ans = min(ans, mn);
    }
    printf("%d\n", ans);
}
