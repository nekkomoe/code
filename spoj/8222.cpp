#include <bits/stdc++.h>

using namespace std;

const int N = 250000 * 2 + 10;

typedef long long ll;

map<int, int> ch[N];

int pre[N], len[N], sz[N], last = 1, cnt = 1, f[N];

int nd(int l) {
    return len[++ cnt] = l, cnt; 
}

void ins(int c) {
    int p, np, q, nq;
    pre[np = last = nd(len[p = last] + 1)] = 1, sz[np] = 1;
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    if(p) {
        pre[np] = q = ch[p][c];
        if(len[p] + 1 != len[q]) {
            nq = nd(len[p] + 1);
            pre[nq] = pre[q], pre[np] = pre[q] = nq;
            ch[nq] = ch[q];
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    }
}

char s[N];

int n, tmp[N], bak[N];

int main() {
    n = strlen(s + scanf("%s", s + 1));
    for(int i = 1 ; s[i] ; ++ i) ins(s[i]);
    for(int i = 1 ; i <= cnt ; ++ i) tmp[len[i]] ++;
    for(int i = 1 ; i <= cnt ; ++ i) tmp[i] += tmp[i - 1];
    for(int i = cnt ; i ; -- i) bak[tmp[len[i]] --] = i;
    for(int i = cnt ; i ; -- i) {
        int x = bak[i];
        sz[pre[x]] += sz[x];
        f[len[x]] = max(f[len[x]], sz[x]);
    }
    for(int i = n ; i ; -- i) f[i] = max(f[i], f[i + 1]);
    for(int i = 1 ; s[i] ; ++ i) printf("%d\n", f[i]);
}
