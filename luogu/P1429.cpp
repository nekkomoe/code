#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200000 + 10;
struct P {
    double x, y;
} p[N], sta[N];
bool cmpx(P a, P b) {
    return a.x < b.x;
}
bool cmpy(P a, P b) {
    return a.y < b.y;
}
double dis(P a, P b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}
double disx(P a, P b) {
    return abs(a.x - b.x);
}
double disy(P a, P b) {
    return abs(a.y - b.y);
}

int n;

double sol(int l, int r) {
    if(l == r) return 1e60;
    else if(l + 1 == r) return dis(p[l], p[r]);
    else {
        int mid = (l + r) >> 1;
        double mnd = min(sol(l, mid), sol(mid + 1, r));
        double res = mnd;
        int top = 0;
        for(int i = l ; i <= r ; ++ i) {
            if(disx(p[i], p[mid]) <= mnd) {
                sta[++ top] = p[i];
            }
        }
        sort(sta + 1, sta + 1 + top, cmpy);
        for(int i = 1 ; i <= top ; ++ i) {
            for(int j = i + 1 ; j <= top && disy(sta[i], sta[j]) <= mnd ; ++ j) {
                res = min(res, dis(sta[i], sta[j]));
            }
        }
        return res;
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%lf%lf", &p[i].x, &p[i].y);
    sort(p + 1, p + 1 + n, cmpx);
    printf("%.4f\n", sol(1, n));
}

