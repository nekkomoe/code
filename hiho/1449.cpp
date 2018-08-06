#include <bits/stdc++.h>

using namespace std;

const int N = 1000010 * 2;

map<int, int> ch[N];

int pre[N], len[N], sz[N], last = 1, cnt = 1;

int nd(int l) {
    return len[++ cnt] = l, cnt;
}

void ins(int c) {
    int p, np, q, nq;
    
    pre[np = last = nd(len[p = last] + 1)] = 1;
    
    sz[np] = 1;
    
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    
    if(p) {
        pre[np] = q = ch[p][c];
        
        if(len[p] + 1 != len[q]) {
            nq = nd(len[p] + 1);
            pre[nq] = pre[q], pre[q] = pre[np] = nq, ch[nq] = ch[q];
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
        
    }
    
}

int n, tmp[N], bak[N], ans[N];

char s[N];

int main() {
    n = strlen(s + scanf("%s", s + 1));
    
    for(int i = 1 ; i <= n ; ++ i) ins(s[i]);
    
    for(int i = 1 ; i <= cnt ; ++ i) tmp[len[i]] ++;
    for(int i = 1 ; i <= cnt ; ++ i) tmp[i] += tmp[i - 1];
    for(int i = cnt ; i ; -- i) bak[tmp[len[i]] --] = i;
    for(int i = cnt ; i ; -- i) sz[pre[bak[i]]] += sz[bak[i]], ans[len[bak[i]]] = max(ans[len[bak[i]]], sz[bak[i]]);
    for(int i = n ; i ; -- i) ans[i] = max(ans[i], ans[i + 1]);
    for(int i = 1 ; i <= n ; ++ i) printf("%d\n", ans[i]);    
}
