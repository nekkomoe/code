#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e6 + 10;

int n, m, q;

struct P {
    ll x, y;
    ll len() { return x * x + y * y; }
} A[N], B[N], C[N];
ll operator * (P a, P b) { return a.x * b.y - b.x * a.y; }
P operator + (P a, P b) { return (P) { a.x + b.x, a.y + b.y }; }
P operator - (P a, P b) { return (P) { a.x - b.x, a.y - b.y }; }

bool cmp_yx(P a, P b) { return a.y < b.y || (a.y == b.y && a.x < b.x); }
bool cmp_angle(P a, P b) { return a * b > 0 || (a * b == 0 && a.len() < b.len()); }


P sta[N];
void getconvex(P *p, int &n) {
    sort(p + 1, p + 1 + n, cmp_yx);
    P bs = p[1];
    for(int i = 1 ; i <= n ; ++ i) p[i] = p[i] - bs;
    sort(p + 2, p + 1 + n, cmp_angle);

    int top = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        while(top >= 2 && (p[i] - sta[top - 1]) * (sta[top] - sta[top - 1]) >= 0) -- top;
        sta[++ top] = p[i];
    }
    n = top;
    for(int i = 1 ; i <= n ; ++ i) p[i] = sta[i] + bs;
}

int tot;
P s1[N], s2[N];

void getminkfu() {
    for(int i = 1 ; i <= n ; ++ i) s1[i] = A[i % n + 1] - A[i];
    for(int i = 1 ; i <= m ; ++ i) s2[i] = B[i % m + 1] - B[i];
    C[tot = 1] = A[1] + B[1];
    int i = 1, j = 1;
    while(i <= n && j <= m) ++ tot, C[tot] = C[tot - 1] + (s1[i] * s2[j] >= 0 ? s1[i ++] : s2[j ++]);
    while(i <= n) ++ tot, C[tot] = C[tot - 1] + s1[i ++];
    while(j <= m) ++ tot, C[tot] = C[tot - 1] + s2[j ++];
}

int check_in(P p) {
    if(p * C[1] > 0 || C[tot] * p > 0) return 0;
    int pos = lower_bound(C + 1, C + 1 + tot, p, cmp_angle) - C - 1;
    return (p - C[pos]) * (C[pos % tot + 1] - C[pos]) <= 0;
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld%lld", &A[i].x, &A[i].y);
    }
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%lld%lld", &B[i].x, &B[i].y);
        B[i].x *= -1, B[i].y *= -1;
    }
    getconvex(A, n), getconvex(B, m);
    getminkfu(), getconvex(C, tot);

    // for(int i = 1 ; i <= n ; ++ i) {
    //     printf("A: (%lld, %lld)\n", A[i].x, A[i].y);
    // }

    // for(int i = 1 ; i <= m ; ++ i) {
    //     printf("B: (%lld, %lld)\n", B[i].x, B[i].y);
    // }

    // for(int i = 1 ; i <= tot ; ++ i) {
    //     printf("C: (%lld, %lld)\n", C[i].x, C[i].y);
    // }

    P bs = C[1], p;
    for(int i = 1 ; i <= tot ; ++ i) C[i] = C[i] - bs;
    for(int i = 1 ; i <= q ; ++ i) {
        scanf("%lld%lld", &p.x, &p.y);
        printf("%d\n", check_in(p - bs));
    }
}
