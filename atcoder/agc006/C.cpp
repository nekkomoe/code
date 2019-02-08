#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int n, m, p[N], tar[N], sta[N], top, vis[N];

ll k, a[N], ans[N];

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &a[i]);
        p[i] = i;
    }
    for(int i = n ; i ; -- i) {
        a[i] -= a[i - 1];
    }
    scanf("%d%lld", &m, &k);
    for(int i = 1 ; i <= m ; ++ i) {
        int x; scanf("%d", &x);
        swap(p[x], p[x + 1]);
    }

    for(int i = 1 ; i <= n ; ++ i) {
        if(vis[i]) continue;
        top = 0;
        sta[top ++] = i;
        int cur = p[i];
        while(cur != i) {
            vis[cur] = 1;
            sta[top ++] = cur;
            cur = p[cur];
        }
        for(int j = 0 ; j < top ; ++ j) {
            tar[sta[j]] = sta[(j + k) % top];
        }
    }

    for(int i = 1 ; i <= n ; ++ i) {
        ans[i] = a[tar[i]] + ans[i - 1];
        printf("%lld.0\n", ans[i]);
    }
}
