#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 300010;
 
int n, ch[N][30], sz[N], fail[N], tot = 1, last;
 
long long ans, len[N];
 
char s[N];
 
int get(int u, int i) {
    while(s[i] != s[i - len[u] - 1]) u = fail[u];
    return u;
}
 
int main() {
     
    scanf("%s", s + 1), n = strlen(s + 1);
     
    len[fail[0] = 1] = -1;
     
    for(int i = 1 ; i <= n ; ++ i) {
        int c = s[i] - 'a';
        int u = get(last, i);
        if(!ch[u][c]) {
            int now = ++ tot; len[now] = len[u] + 2;
            fail[now] = ch[get(fail[u], i)][c];
            ch[u][c] = now;
        }
         
        sz[last = ch[u][c]] ++;
    }
     
    for(int i = tot ; i ; -- i) sz[fail[i]] += sz[i], ans = max(ans, sz[i] * len[i]);
     
    printf("%lld\n", ans);
}
