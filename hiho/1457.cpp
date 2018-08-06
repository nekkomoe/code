#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1000000 * 2 + 10;

const int mod = 1e9 + 7;

map<int, int> ch[N];

int pre[N], len[N], last = 1, cnt = 1, n, tmp[N], bak[N];

ll dp[N], sz[N], ans;

char s[N];

int nd(int l) {
    return len[++ cnt] = l, cnt;
}

void ins(int c) {
    int p, np, q, nq;
    pre[np = last = nd(len[p = last] + 1)] = 1;
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    if(p) {
        pre[np] = q = ch[p][c];
        if(len[p] + 1 != len[q]) {
            nq = nd(len[p] + 1), ch[nq] = ch[q], pre[nq] = pre[q], pre[q] = pre[np] = nq;
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%s", s + 1);
        for(int j = 1 ; s[j] ; ++ j) ins(s[j]);
        if(i < n) ins('#');
    }
    for(int i = 1 ; i <= cnt ; ++ i) tmp[len[i]] ++;
    for(int i = 1 ; i <= cnt ; ++ i) tmp[i] += tmp[i - 1];
    for(int i = cnt ; i ; -- i) bak[tmp[len[i]] --] = i;
    sz[1] = 1;
    for(int i = 1 ; i <= cnt ; ++ i) {
        int u = bak[i];
        for(map<int, int> :: iterator it = ch[u].begin() ; it != ch[u].end() ; ++ it) {
            int c = it -> first, v = it -> second;
            if(c == '#') continue;
            c -= '0';
            sz[v] = (sz[v] + sz[u]) % mod;
            dp[v] = (dp[v] + dp[u] * 10 + c * sz[u]) % mod;
        }
    }
    
    for(int i = 1 ; i <= cnt ; ++ i) ans = (ans + dp[i]) % mod;
    printf("%lld\n", ans);
    
}
