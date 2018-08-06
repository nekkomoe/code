#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
#include <cmath>
 
#ifdef ONLINE_JUDGE
    #define debug
#else
    #define debug printf("passing [%s] in line %d\n", __FUNCTION__, __LINE__)
#endif
 
using namespace std;
 
typedef long long ll;
 
const int N = 100010;
 
ll bit[N], a[N];
 
int fa[N], n, m;
 
int get(int x) {
    return x == fa[x] ? x : fa[x] = get(fa[x]);
}
 
void add(int i, ll v) {
    for( ; i <= n ; i += i & -i) {
        bit[i] += v;
    }
}
 
ll sum(int i) {
    ll ret = 0;
    for( ; i ; i -= i & -i) {
        ret += bit[i];
    }
    return ret;
}
 
int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &a[i]);
        add(i, a[i]);
        fa[i] = i;
    }
    fa[n + 1] = n + 1;
    scanf("%d", &m);
    for(int i = 1, op, l, r ; i <= m ; ++ i) {
        scanf("%d%d%d", &op, &l, &r);
        if(op == 1) {
            printf("%lld\n", sum(r) - sum(l - 1));
        } else {
            for(int j = l ; j <= r ; j = get(j) == j ? j + 1 : get(j)) {
                add(j, (ll)sqrt(a[j]) - a[j]);
                a[j] = (ll)sqrt(a[j]);
                a[j] <= 1 && (fa[j] = j + 1);
            }
        }
    }
}
