// 决策单调性 斜率优化

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 60010;

typedef long long ll;

int n;

struct QUE {
    int l, r, k;
} que[N];

ll L, f[N], sum[N], head, tail;

inline ll sqr(ll x) { return x * x; }

ll calc(ll j, ll i) {
    return f[j] + sqr(i - j + sum[i] - sum[j] - 1 - L);
}

int get(QUE t, int i) {
    int l = t.l, r = t.r;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(calc(i, mid) < calc(t.k, mid)) r = mid - 1;
        else l = mid + 1;
    }
    return l;
}

int main() {
    scanf("%d%lld", &n, &L);
    for(int i = 1 ; i <= n ; ++ i) scanf("%lld", &sum[i]), sum[i] += sum[i - 1];
    que[head = tail = 1] = (QUE) {0, n, 0};
    for(int i = 1 ; i <= n ; ++ i) {
        while(head <= tail && i > que[head].r) ++ head;
        f[i] = calc(que[head].k, i);
        if(head > tail || calc(i, n) < calc(que[tail].k, n)) {
            while(head <= tail && calc(i, que[tail].l) < calc(que[tail].k, que[tail].l)) -- tail;
            if(head <= tail) {
                int p = get(que[tail], i);
                que[tail].r = p - 1;
                que[++ tail] = (QUE) {p, n, i};
            } else {
                que[++ tail] = (QUE) {i, n, i};
            }
        }
    }
    printf("%lld\n", f[n]);
}