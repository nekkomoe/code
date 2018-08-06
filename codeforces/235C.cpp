#include <bits/stdc++.h>

using namespace std;

const int N = 1000000 * 2 * 2 + 10;

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
            nq = nd(len[p] + 1), ch[nq] = ch[q], pre[nq] = pre[q], pre[q] = pre[np] = nq;
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    }
}

int n, q, tmp[N], bak[N], flag[N];

char s[N];

typedef long long ll;

int main() {
    n = strlen(s + scanf("%s", s + 1));
    for(int i = 1 ; i <= n ; ++ i) ins(s[i]);
    for(int i = 1 ; i <= cnt ; ++ i) tmp[len[i]] ++;
    for(int i = 1 ; i <= cnt ; ++ i) tmp[i] += tmp[i - 1];
    for(int i = cnt ; i ; -- i) bak[tmp[len[i]] --] = i;
    for(int i = cnt ; i ; -- i) {
        int x = bak[i];
        sz[pre[x]] += sz[x];
    }
    scanf("%d", &q);
    for(int t = 1 ; t <= q ; ++ t) {
        ll ans = 0;
        n = strlen(s + scanf("%s", s + 1));
        for(int i = 1 ; i <= n ; ++ i) s[i + n] = s[i];
        for(int i = 1, p = 1, l = 0 ; i <= n * 2 ; ++ i) {
            int c = s[i];
            while(p && !ch[p][c]) p = pre[p], l = len[p];
            if(ch[p][c]) ++ l, p = ch[p][c];
            else p = 1, l = 0;
            if(l > n) while(len[pre[p]] >= n) p = pre[p], l = len[p];
            if(l >= n && flag[p] != t) {
                ans += sz[p];
                flag[p] = t;
            }
        }
        cout << ans << endl;
    }
}
