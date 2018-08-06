#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, p = 1e9 + 7;
char s[N];
 
int pw(int a, int b) {
    int r = 1;
    for( ; b ; b >>= 1, a = (long long) a * a % p) if(b & 1) r = (long long) r * a % p;
    return r;
}
 
int pre[N][4]; // 0:A 1:B 2:C 3:?
int sub[N][4];
 
int main() {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    for(int i = 1 ; i <= n ; ++ i) {
        memcpy(pre[i], pre[i - 1], sizeof pre[i]);
        pre[i][s[i] == '?' ? 3 : s[i] - 'A'] ++;
    }
    for(int i = n ; i ; -- i) {
        memcpy(sub[i], sub[i + 1], sizeof sub[i]);
        sub[i][s[i] == '?' ? 3 : s[i] - 'A'] ++;
    }
    long long ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        // cout << pre[i][0] << ' ' << pre[i][1] << ' ' << pre[i][2] << ' ' << pre[i][3] << endl;
        if(s[i] == 'B' || s[i] == '?') {
            
            // cout << "count in: " << i << endl;
            
            long long x = 0;
            long long y = 0;
            x = (long long) pre[i - 1][0] * pw(3, pre[i - 1][3]) % p;
            if(pre[i - 1][3]) y = (long long) pre[i - 1][3] * pw(3, pre[i - 1][3] - 1) % p;
            
            long long z = x + y;
            
            x = y = 0;
            x = (long long) sub[i + 1][2] * pw(3, sub[i + 1][3]) % p;
            if(sub[i + 1][3]) y = (long long) sub[i + 1][3] * pw(3, sub[i + 1][3] - 1) % p;
                        
            ans = (ans + z * (x + y) % p) % p;
            
        }
    }
    printf("%lld\n", ans);
}
