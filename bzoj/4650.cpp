#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
const int N = 30010;
 
#define ms(a) memset(a, 0, sizeof a)
 
int n, T;
 
char s[N];
 
struct SA {
 
    int sa[N], rk[N], a[N], b[N], cnta[N], cntb[N], tmp[N], mn[N][30];
 
    char s[N];
 
    void build() {
        ms(sa), ms(rk), ms(a), ms(b), ms(cnta), ms(cntb), ms(tmp), ms(mn);
        for(int i = 1 ; i <= n ; ++ i) cnta[s[i]] ++;
        for(int i = 'a' ; i <= 'z' ; ++ i) cnta[i] += cnta[i - 1];
        for(int i = n ; i ; -- i) sa[cnta[s[i]] --] = i;
        for(int i = 'a' ; i <= 'z' ; ++ i) cnta[i] = 0;
        rk[sa[1]] = 1;
        for(int i = 2 ; i <= n ; ++ i) rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
        for(int k = 1 ; rk[sa[n]] < n ; k <<= 1) {
            for(int i = 1 ; i <= n ; ++ i) cnta[i] = cntb[i] = 0;
            for(int i = 1 ; i <= n ; ++ i) cnta[a[i] = rk[i]] ++, cntb[b[i] = i + k <= n ? rk[i + k] : 0] ++;
            for(int i = 1 ; i <= n ; ++ i) cnta[i] += cnta[i - 1], cntb[i] += cntb[i - 1];
            for(int i = n ; i ; -- i) tmp[cntb[b[i]] --] = i;
            for(int i = n ; i ; -- i) sa[cnta[a[tmp[i]]] --] = tmp[i];
            rk[sa[1]] = 1;
            for(int i = 2 ; i <= n ; ++ i) rk[sa[i]] = rk[sa[i - 1]] + (a[sa[i]] != a[sa[i - 1]] || b[sa[i]] != b[sa[i - 1]]);
        }
        for(int i = 1, j = 0 ; i <= n ; ++ i) {
            if(j) -- j;
            while(s[i + j] == s[sa[rk[i] - 1] + j]) ++ j;
            mn[rk[i]][0] = j;
        }
        for(int j = 1 ; j <= 25 ; ++ j) {
            for(int i = 1 ; i + (1 << j) - 1 <= n ; ++ i) {
                mn[i][j] = min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
 
    int getmin(int x, int y) {
        if(x > y) swap(x, y);
        ++ x;
        int ret = mn[x][0];
        for(int i = 25 ; ~i ; -- i) {
            if(x + (1 << i) - 1 <= y) {
                ret = min(ret, mn[x][i]);
                x += 1 << i;
            }
        }
        return ret;
    }
 
    int getlcp(int x, int y) {
        return getmin(rk[x], rk[y]);
    }
 
} a, b;
 
long long pre[N], sub[N], ans;
 
#define add(arr, l, r) (arr[l] ++, arr[r + 1] --)
 
void sol() {
    scanf("%s", s + 1), n = strlen(s + 1);
    ms(a.s), ms(b.s);
    for(int i = 1 ; s[i] ; ++ i) a.s[i] = s[i], b.s[n - i + 1] = s[i];
    a.build();
    b.build();
    ms(pre), ms(sub), ans = 0;
 
    for(int L = 1 ; 2 * L <= n ; ++ L) {
        for(int i = L ; i + L <= n ; i += L) {
            int p1 = i, p2 = i + L;
            if(s[p1] != s[p2]) continue;
            int x = b.getlcp(n - p1 + 1, n - p2 + 1);
            int y = a.getlcp(p1, p2);
            x = min(x, L);
            y = min(y, L);
            int len = x + y - 1;
            if(len < L) continue;
            add(pre, p2 - x + L, p2 + y - 1);
            add(sub, p1 - x + 1, p1 + y - L);
 
        }
    }
 
    for(int i = 1 ; i <= n ; ++ i) pre[i] += pre[i - 1], sub[i] += sub[i - 1];
    for(int i = 1 ; i < n ; ++ i) ans += pre[i] * sub[i + 1];
    printf("%lld\n", ans);
}
 
int main() {
    scanf("%d", &T);
    while(T --) {
        sol();
    }
}
