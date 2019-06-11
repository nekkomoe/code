#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct PR {
    int l, r;
};
bool operator < (PR a, PR b) {
    return a.l == b.l ? a.r > b.r : a.l < b.l;
}
const int N = 1e5 + 10;
PR a[N];
int b[N];

void runprog() {
    priority_queue<int, vector<int>, greater<int> > pq;
    int ans = 0, n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d%d", &a[i].l, &a[i].r);
    }
    sort(a + 1, a + 1 + n);
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%d", &b[i]);
    }
    sort(b + 1, b + 1 + m);
    for(int i = 1, j = 1 ; i <= m ; ++ i) {
        while(j <= n && a[j].l <= b[i]) {
            pq.emplace(a[j].r);
            ++ j;
        }
        while(pq.size() && pq.top() < b[i]) {
            pq.pop();
        }
        ans = max(ans, n - (int) pq.size() + 1);
        if(ans > n) {
            break;
        }
        pq.pop();
    }

    static int T = 0;
    if(ans > n) {
        printf("Case #%d: IMPOSSIBLE!\n", ++ T);
    } else {
        printf("Case #%d: %d\n", ++ T, ans);
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
