#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

struct P {
    ll x, y;
    int id;
} pts[N];
P operator - (P a, P b) {
    return (P) { a.x - b.x, a.y - b.y };
}
ll operator * (P a, P b) {
    return a.x * b.y - b.x * a.y;
}

P sta[N]; int top;
int n;
int vis[N];
int l[N], r[N];
ll w[N];
int main() {
    int nct;
    scanf("%d", &nct);
    pts[++ n] = (P) { 0, 0, 1 };
    for(int i = 1 ; i <= nct ; ++ i) {
        int y; scanf("%d", &y);
        w[i + 1] = y;
        pts[++ n] = (P) { i, y, i + 1 };
    }
    pts[++ n] = (P) { nct + 1, 0, nct + 2 };
    
//    for(int i = 1 ; i <= n ; ++ i) {
//        printf(": %lld, %lld\n", pts[i].x, pts[i].y);
//    }
    
    for(int i = 1 ; i <= n ; ++ i) {
        P p = pts[i];
        while(top >= 2 && (p - sta[top]) * (sta[top - 1] - sta[top]) >= 0) -- top;
        sta[++ top] = p;
    }
    for(int i = 1 ; i <= top ; ++ i) {
        vis[sta[i].id] = 1;
//        printf("(%lld, %lld)\n", sta[i].x, sta[i].y);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        if(vis[i]) {
            l[i] = i;
        } else {
            l[i] = l[i - 1];
        }
        if(!l[i]) l[i] = 1;
    }
    for(int i = n ; i >= 1 ; -- i) {
        if(vis[i]) {
            r[i] = i;
        } else {
            r[i] = r[i + 1];
        }
        if(!r[i]) r[i] = n;
    }
    const int coef = 1e5;
    for(int i = 2 ; i < n ; ++ i) {
        if(l[i] == r[i]) {
            printf("%lld\n", coef * w[i]);
        } else {
//            printf("[%d, %d]\n", l[i], r[i]);
            double ans = 1e5 * (w[l[i]] * (r[i] - i) + w[r[i]] * (i - l[i])) / (r[i] - l[i]);
            printf("%.0lf\n", floor(ans));
        }
    }
}
