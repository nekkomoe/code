#include "bits/stdc++.h"
typedef long long ll;
using namespace std;
 
const int N = 2e6 + 10, LEN = 330;
char s[N];
int p, q, np, nq, ch[N][30], last = 1, cnt = 1, pre[N], len[N], sz[N], tmp[N], bak[N], fa[N][21];
int nd(int l) { return len[++ cnt] = l, cnt; }
void ins(int c) {
    pre[last = np = nd(len[p = last] + 1)] = 1, sz[np] = 1;
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    if(p) {
        pre[np] = q = ch[p][c];
        if(len[p] + 1 != len[q]) {
            pre[nq = nd(len[p] + 1)] = pre[q], pre[q] = pre[np] = nq;
            memcpy(ch[nq], ch[q], sizeof ch[q]);
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    }
}

int n, m, Q, K, ql[N], qr[N];
char W[N];

namespace neko_one {
    vector<int> nya[LEN + 10][LEN + 10];
    void runprog () {
        for(int i = 1 ; i <= m ; ++ i) {
            nya[ql[i]][qr[i]].push_back(i);
        }
        for(int i = 1 ; i <= K ; ++ i) {
            for(int j = i ; j <= K ; ++ j) {
                sort(nya[i][j].begin(), nya[i][j].end());
            }
        }
        while(Q --) {
            int a, b;
            scanf("%s%d%d", W + 1, &a, &b);
            ++ a, ++ b;
            ll ans = 0;
            for(int i = 1 ; i <= K ; ++ i) {
                int u = 1;
                for(int j = i ; j <= K ; ++ j) {
                    if(ch[u][W[j] - 'a']) {
                        u = ch[u][W[j] - 'a'];

                        if(nya[i][j].empty()) continue;
                        if(nya[i][j][0] > b || nya[i][j].back() < a) continue;

                        ll L = lower_bound(nya[i][j].begin(), nya[i][j].end(), a) - nya[i][j].begin();
                        ll R = upper_bound(nya[i][j].begin(), nya[i][j].end(), b) - 1 - nya[i][j].begin();

                        ll cnt = R - L + 1;

                        // cnt = 0;
                        // for(int x: nya[i][j]) {
                        //     cnt += a <= x && x <= b;
                        // }

                        ans += sz[u] * cnt;
                        // printf("str[%d, %d], sz = %d, cnt = %lld\n", i, j, sz[u], cnt);
                    } else {
                        break;
                    }
                }
            }
            printf("%lld\n", ans);
        }
    }
}

// abacdaba
// dab
// 1 3
// 2 3
// 1 1
// 3 3
// 2 3

namespace neko_two {

    int pts[N], L[N];

    void runprog () {
        while(Q --) {
            int a, b; scanf("%s%d%d", W + 1, &a, &b); ++ a, ++ b;
            ll ans = 0;

            int u = 1;
            for(int i = 1 ; i <= K ; ++ i) {
                L[i] = L[i - 1], pts[i] = 0;
                int c = W[i] - 'a';
                while(!ch[u][c] && u) {
                    u = pre[u], L[i] = len[u];
                }
                if(ch[u][c]) u = ch[u][c], ++ L[i];
                else u = 1, L[i] = 0;
                pts[i] = u;

                // printf("L[%d] = %d, u = %d, lenu = %d, sz = %d\n", i, L[i], u, len[u], sz[u]);
            }

            for(int T = a ; T <= b ; ++ T) {
                int u = pts[qr[T]];
                int tar_len = qr[T] - ql[T] + 1;
                
                if(L[qr[T]] < tar_len) continue;

                for(int j = 20 ; ~ j ; -- j) {
                    if(len[fa[u][j]] >= tar_len) {
                        u = fa[u][j];
                    }
                }
                // while(u && len[pre[u]] >= tar_len) {
                //     u = pre[u];
                // }
                if(len[u] >= tar_len) {
                    ans += sz[u];
                }

                // printf("in %d, += %d\n", T, sz[u]);
            }

            printf("%lld\n", ans);
        }
    }
}

int main() {
    scanf("%d%d%d%d", &n, &m, &Q, &K);
    scanf("%s", s + 1);
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%d%d", &ql[i], &qr[i]);
        ++ ql[i], ++ qr[i];
    }
    for(int i = 1 ; i <= n ; ++ i) ins(s[i] - 'a');
    for(int i = 1 ; i <= cnt ; ++ i) tmp[len[i]] ++;
    for(int i = 1 ; i <= cnt ; ++ i) tmp[i] += tmp[i - 1];
    for(int i = cnt ; i ; -- i) bak[tmp[len[i]] --] = i;
    for(int i = cnt ; i ; -- i) {
        sz[pre[bak[i]]] += sz[bak[i]];
        fa[bak[i]][0] = pre[bak[i]];
    }
    for(int j = 1 ; j <= 20 ; ++ j) {
        for(int i = 1 ; i <= cnt ; ++ i) {
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
        }
    }

    if(K <= LEN) {
        neko_one :: runprog();
    } else {
        neko_two :: runprog();
    }
}
