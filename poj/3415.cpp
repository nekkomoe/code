#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <map>

using namespace std;

const int N = 2e5 + 10;

int n, len[N], pre[N], tag[N], sz[N], tot, last, ch[N][60];

typedef long long ll;

ll ans;

int nd(int l) { return len[++ tot] = l, tot;  }

void ins(int c) {
    int p, np, q, nq;
    pre[np = last = nd(len[p = last] + 1)] = 1, sz[np] = 1;
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    if(p) {
        pre[np] = q = ch[p][c];
        if(len[p] + 1 != len[q]) {
            nq = nd(len[p] + 1), memcpy(ch[nq], ch[q], sizeof ch[q]), pre[nq] = pre[q], pre[np] = pre[q] = nq;
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    }
}

void init() {
    ans = 0;
    for(int i = 0 ; i <= tot ; ++ i) memset(ch[i], 0, sizeof ch[i]), sz[i] = len[i] = pre[i] = tag[i] = 0;
    tot = last = 1;
}

char a[N], b[N];

int tmp[N], bak[N], k;

void sol() {
    init();
    scanf("%s%s", a + 1, b + 1), n = strlen(a + 1);
    for(int i = 1 ; i <= n ; ++ i) a[i] = (islower(a[i]) ? a[i] - 'a' : a[i] - 'A' + 26), b[i] = (islower(b[i]) ? b[i] - 'a' : b[i] - 'A' + 26);
    for(int i = 1 ; i <= n ; ++ i) ins(a[i]);
    memset(tmp, 0, sizeof tmp), memset(bak, 0, sizeof bak);
    for(int i = 1 ; i <= tot ; ++ i) tmp[len[i]] ++;
    for(int i = 1 ; i <= tot ; ++ i) tmp[i] += tmp[i - 1];
    for(int i = tot ; i ; -- i) bak[tmp[len[i]] --] = i;
    for(int i = tot ; i ; -- i) sz[pre[bak[i]]] += sz[bak[i]];
    for(int i = 1, p = 1, l = 0 ; i <= n ; ++ i) {
        int c = b[i];
        if(ch[p][c]) {
            ++ l, p = ch[p][c];
        } else {
            while(p && !ch[p][c]) p = pre[p];
            if(p) l = len[p] + 1, p = ch[p][c]; else l = 0, p = 1;
        }
        if(l >= k) {
            ans += (ll) sz[p] * (l - max(k, len[pre[p]] + 1) + 1);
            if(len[pre[p]] >= k) tag[pre[p]] ++;
        }
    }
    for(int i = tot ; i ; -- i) {
        int p = bak[i];
        ans += (ll) sz[p] * tag[p] * (len[p] - max(k, len[pre[p]] + 1) + 1);
        if(len[pre[p]] >= k) tag[pre[p]] += tag[p];
    }
    printf("%lld\n", ans);
}

int main() {
    while(scanf("%d", &k), k) {
        sol();
    }
}

