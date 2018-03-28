#include <cstdio>
#include <bitset>
#include <algorithm>
using namespace std;
 
const int N = 210000;
int n, m, c = 100002, cnt[N], a[N], b[N], len = 300, ans[N];
bitset<100002> f, g;
struct Q {
    int type, x, l, r, id;
} q[N];
bool operator < (Q a, Q b) {
    return a.l / len == b.l / len ? a.r < b.r : a.l / len < b.l / len;
}
void add(int i) {
    if(++ cnt[a[i]] == 1) {
        f[a[i]] = 1;
        g[b[i]] = 1;
    }
}
void del(int i) {
    if(-- cnt[a[i]] == 0) {
        f[a[i]] = 0;
        g[b[i]] = 0;
    }
}
int query(Q q) {
    if(q.type == 1) {
        return ((f >> q.x) & f).count();
    } else if(q.type == 2) {
        return ((g >> (c - q.x)) & f).count();
    } else if(q.type == 3) {
        for(int i = 1 ; i * i <= q.x ; ++ i) {
            if(q.x % i == 0 && f[i] && f[q.x / i]) {
                return 1;
            }
        }
    }
    return 0;
}
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]), b[i] = c - a[i];
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%d%d%d%d", &q[i].type, &q[i].l, &q[i].r, &q[i].x);
        q[i].id = i;
    }
    sort(q + 1, q + 1 + m);
    for(int i = q[1].l ; i <= q[1].r ; ++ i) add(i);
    ans[q[1].id] = query(q[1]);
    int l = q[1].l, r = q[1].r;
    for(int i = 2 ; i <= m ; ++ i) {
        while(r < q[i].r) add(++ r);
        while(l > q[i].l) add(-- l);
        while(r > q[i].r) del(r --);
        while(l < q[i].l) del(l ++);
        ans[q[i].id] = query(q[i]);
    }
    for(int i = 1 ; i <= m ; ++ i) {
        if(ans[i]) {
            puts("yuno");
        } else {
            puts("yumi");
        }
    }
}
