#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 5e5 + 10;

int n, m, L, R, a[N], s[N];

int mn[N][30];

int getmn(int a, int b) {
    return s[a] < s[b] ? a : b;
}

int lg[N];

int ask(int a, int b) {
    if(a > b) return -1;
    int k = lg[b - a + 1];
    return getmn(mn[a][k], mn[b - (1 << k) + 1][k]);
}

struct T {
    int sum, pos, a, b;
};
bool operator < (T a, T b) {
    return a.sum < b.sum;
    // return make_pair(make_pair(a.sum, a.pos), make_pair(a.a, a.b)) < 
    //        make_pair(make_pair(b.sum, b.pos), make_pair(b.a, b.b));
}
priority_queue<T> pq;

int main() {
    scanf("%d%d%d%d", &n, &m, &L, &R);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        s[i] = s[i - 1] + a[i];
        mn[i][0] = i;
    }
    for(int i = 2 ; i <= n + 5 ; ++ i) {
        lg[i] = lg[i >> 1] + 1;
    }
    for(int j = 1 ; j <= 25 ; ++ j) {
        for(int i = 0 ; i + (1 << j) - 1 <= n ; ++ i) {
            mn[i][j] = getmn(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
        }
    }
    for(int i = L ; i <= n ; ++ i) {
        int l = max(0, i - R), r = i - L;
        pq.push((T) { s[i] - s[ask(l, r)], i, l, r });
    }
    ll ans = 0;
    while(m --) {
        T top = pq.top(); pq.pop();
        ans += top.sum;
        int a = top.a, b = top.b, pos = top.pos;
        int y = ask(a, b);
        int l = ask(a, y - 1);
        int r = ask(y + 1, b);
        if(l != -1) {
            pq.push((T) { s[pos] - s[l], pos, a, y - 1 });
        }
        if(r != -1) {
            pq.push((T) { s[pos] - s[r], pos, y + 1, b });
        }
    }
    printf("%lld\n", ans);
}
