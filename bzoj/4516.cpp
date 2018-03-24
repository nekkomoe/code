#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 200010;
 
int n, len[N], pre[N], last = 1, cnt = 1;
 
map<int, int> ch[N];
 
long long ans;
 
int f(int p) { return len[p] - len[pre[p]]; }
 
int nd(int l) { return len[++ cnt] = l, cnt; }
 
void ins(int c) {
    int p, np, q, nq;
    np = last = nd(len[p = last] + 1);
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    if(p) {
        q = ch[p][c];
        if(len[p] + 1 != len[q]) {
            nq = nd(len[p] + 1);
            pre[nq] = pre[q], ans += f(nq) - f(q);
            pre[q] = pre[np] = nq, ans += f(q) + f(np);
            ch[nq] = ch[q];
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        } else {
            pre[np] = q, ans += f(np);
        }
    } else {
        pre[np] = 1, ans += f(np);
    }
}
 
int main() {
    scanf("%d", &n);
    for(int i = 1, x ; i <= n ; ++ i) {
        scanf("%d", &x), ins(x), printf("%lld\n", ans);
    }
}
