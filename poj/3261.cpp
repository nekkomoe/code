#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>

using namespace std;

const int N = 4e5 + 10;

int n, k, pre[N], len[N], sz[N], cnt = 1, last = 1, bak[N], tmp[N], ans;

map<int, int> ch[N];

int nd(int l) { return len[++ cnt] = l, cnt; }

void ins(int c) {
    int p, np, q, nq;
    pre[np = last = nd(len[p = last] + 1)] = 1, sz[np] = 1;
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    if(p) {
        pre[np] = q = ch[p][c];
        if(len[p] + 1 != len[q]) {
            nq = nd(len[p] + 1), pre[nq] = pre[q], pre[np] = pre[q] = nq;
            ch[nq] = ch[q];
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    } 
}

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1, x ; i <= n ; ++ i) {
        scanf("%d", &x), ins(x);
    }
    for(int i = 1 ; i <= cnt ; ++ i) tmp[len[i]] ++;
    for(int i = 1 ; i <= cnt ; ++ i) tmp[i] += tmp[i - 1];
    for(int i = cnt ; i ; -- i) bak[tmp[len[i]] --] = i;
    for(int i = cnt ; i ; -- i) {
        int x = bak[i];
        sz[pre[x]] += sz[x];
        if(sz[x] >= k) ans = max(ans, len[x]);
    }
    printf("%d\n", ans);
}
