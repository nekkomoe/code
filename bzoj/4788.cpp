// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 22;
int cnt[1 << N];
int vis[1 << N];
ll p[N], q[N];
ll a[1 << N], b[1 << N], ta, tb, T, ans;
int n, m, l[1 << N], r[1 << N];

int main() {
    for(int i = 1 ; i < (1 << N) ; ++ i) {
        cnt[i] = cnt[i >> 1] + (i & 1);
    }
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        char s[30];
        scanf("%s", s + 1);
        for(int j = 1 ; j <= m ; ++ j) {
            if(s[j] == '1') {
                l[1 << (i - 1)] |= 1 << (j - 1);
                r[1 << (j - 1)] |= 1 << (i - 1);
            }
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &p[i]);
    }
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%lld", &q[i]);
    }
    scanf("%lld", &T);

    memset(vis, 0, sizeof vis);
    vis[0] = 1;
    for(int s = 1 ; s < (1 << n) ; ++ s) {
        ll sum = 0;
        vis[s] = 1;
        for(int i = 1 ; i <= n ; ++ i) {
            if((s >> (i - 1)) & 1) {
                sum += p[i];
                vis[s] &= vis[s ^ (1 << (i - 1))];
                l[s] |= l[s ^ (1 << (i - 1))];
            }
        }
        if(!vis[s]) continue;
        if(cnt[l[s]] >= cnt[s]) {
            a[++ ta] = sum;
        } else {
            vis[s] = 0;
        }
    }

    memset(vis, 0, sizeof vis);
    vis[0] = 1;
    for(int s = 1 ; s < (1 << m) ; ++ s) {
        ll sum = 0;
        vis[s] = 1;
        for(int i = 1 ; i <= m ; ++ i) {
            if((s >> (i - 1)) & 1) {
                sum += q[i];
                vis[s] &= vis[s ^ (1 << (i - 1))];
                r[s] |= r[s ^ (1 << (i - 1))];
            }
        }
        if(!vis[s]) continue;
        if(cnt[r[s]] >= cnt[s]) {
            b[++ tb] = sum;
        } else {
            vis[s] = 0;
        }
    }

    sort(a + 1, a + 1 + ta);
    sort(b + 1, b + 1 + tb);

    for(int i = tb, j = 0 ; i >= 0 ; -- i) {
        while(j <= ta && a[j] + b[i] < T) {
            ++ j;
        }
        ans += ta - j + 1;
    }    

    printf("%lld\n", ans);
}
