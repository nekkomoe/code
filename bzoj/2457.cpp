#include <cstdio>
#include <set>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10;

struct Q {
    int val, pos;
} q[N];

int n, mn[N], mx[N];

bool operator < (Q a, Q b) {
    return a.val == b.val ? a.pos < b.pos : a.val < b.val;
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &q[i].val), q[i].pos = i;
    }
    sort(q + 1, q + 1 + n);
    int cnt = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        if(q[i].val != q[i - 1].val) {
            mx[cnt] = q[i - 1].pos;
            mn[++ cnt] = q[i].pos;
        }
    }
    mx[cnt] = q[n].pos;
    int ans = 0, h = 0x3f3f3f3f, t = 1;
    for(int i = 1 ; i <= cnt ; ++ i) {
        if(t) {
            if(h < mn[i]) h = mx[i];
            else ++ ans, h = mn[i], t = 0;
        } else {
            if(h > mx[i]) h = mn[i];
            else h = mx[i], t = 1;
        }
    }
    printf("%d\n", ans);
}

