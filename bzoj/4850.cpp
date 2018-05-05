#include <bits/stdc++.h>

using namespace std;

const int N = 500000 + 10;

struct data {
    int l, r, p;
} dt[N];

int n, a[N], l, r;

double f[N], g[N];

double calc(int j, int i) {
    return a[j] + sqrt(abs(i - j)) - a[i];
}

int get(data p, int i) {
    int l = p.l, r = p.r;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(calc(p.p, mid) > calc(i, mid)) l = mid + 1;
        else r = mid - 1;
    }
    return l;
}

void sol(double *f) {
    for(int i = 1 ; i <= n ; ++ i) {
//        while(l <= r && dt[l].r < i) l ++;
        dt[l].l ++;
        if(l <= r && dt[l].r < dt[l].l) l ++;
        if(l > r || calc(i, n) > calc(dt[r].p, n)) {
            while(l <= r && calc(dt[r].p, dt[r].l) < calc(i, dt[r].l)) r --;
            if(l <= r) {
                int t = get(dt[r], i);
                dt[r].r = t - 1;
                dt[++ r] = (data) { t, n, i };
            } else {
                dt[++ r] = (data) { i, n, i };
            }
        }
        f[i] = calc(dt[l].p, i);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }
    
    sol(f);
    
    reverse(a + 1, a + 1 + n);
    
    sol(g);
    
    for(int i = 1 ; i <= n ; ++ i) {
        printf("%d\n", max(0, (int) ceil(max(f[i], g[n - i + 1]))));
    }
}
