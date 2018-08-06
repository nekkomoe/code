#include <cstdio>
#include <cstring>
#include <map>

using namespace std;

const int N = 2e5 + 10;

int n;

int pre[N], len[N], tot = 1, last = 1;

map<int, int> ch[N];

long long ans;

char s[N];

int nd(int l) {
    return len[++ tot] = l, tot;
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

void sol() {
    memset(len, 0, sizeof len), memset(pre, 0, sizeof pre);
    for(int i = 1 ; i <= tot ; ++ i) ch[i].clear();
    tot = last = 1;
    ans = 0;
    scanf("%s", s + 1), n = strlen(s + 1);
    for(int i = 1 ; i <= n ; ++ i) ins(s[i] - 'A');
    for(int i = 1 ; i <= tot ; ++ i) ans += len[i] - len[pre[i]];
    printf("%lld\n", ans);
}

int main() {
    int T; scanf("%d", &T);
    while(T --) sol();
}
