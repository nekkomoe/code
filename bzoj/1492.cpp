#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10;

const double inf = 1e9;

const double eps = 1e-7;

struct Q {
    double a,b, rat, k;
    int id;
} q[N], qt[N];

bool operator < (Q x, Q y) {
    return x.k < y.k;
}

struct P {
    double x, y;
} p[N], pt[N];

int cmp(double a, double b) {
    return fabs(a - b) < eps;
}

bool operator < (P x, P y) {
    return x.x < y.x + eps || (cmp(x.x, y.x) && x.y < y.y + eps);
}

int n, sta[N];

double f[N];

double slp(int i, int j) {
    if(!i) return -inf;
    if(!j) return inf;
    if(cmp(p[i].x, p[j].x)) return -inf;
    return (p[i].y - p[j].y) / (p[i].x - p[j].x);
}

void cdq(int l, int r) {
    if(l == r) {
        f[l] = max(f[l], f[l - 1]);
        p[l].y = f[l] / (q[l].a * q[l].rat + q[l].b);
        p[l].x = p[l].y * q[l].rat;
    } else {
        int mid = (l + r) >> 1, l1 = l, l2 = mid + 1;
        for(int i = l ; i <= r ; ++ i) {
            if(q[i].id <= mid) {
                qt[l1 ++] = q[i];
            } else {
                qt[l2 ++] = q[i];
            }
        }
        for(int i = l ; i <= r ; ++ i) {
            q[i] = qt[i];
        }
        cdq(l, mid);
        int tp = 0;
        for(int i = l ; i <= mid ; ++ i) {
            while(tp > 1 && slp(i, sta[tp]) + 1e-7 > slp(sta[tp], sta[tp - 1])) {
                -- tp;
            }
            sta[++ tp] = i;
        }
        int _ = 1;
        for(int i = r ; i > mid ; -- i) {
            while(_ < tp && q[i].k < slp(sta[_], sta[_ + 1])) {
                ++ _;
            }
            f[q[i].id] = max(f[q[i].id], p[sta[_]].x * q[i].a + p[sta[_]].y * q[i].b);
        }
        cdq(mid + 1, r);
        l1 = l, l2 = mid + 1;
        for(int i = l ; i <= r ; ++ i) {
            if((p[l1] < p[l2] || l2 > r) && l1 <= mid) {
                pt[i] = p[l1 ++];
            } else {
                pt[i] = p[l2 ++];
            }
        }
        for(int i = l ; i <= r ; ++ i) {
            p[i] = pt[i];
        }
    }
}

int main() {
    scanf("%d%lf", &n, &f[0]);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lf%lf%lf", &q[i].a, &q[i].b, &q[i].rat), q[i].id = i;
        q[i].k = - q[i].a / q[i].b;
    }
    sort(q + 1, q + 1 + n);
    cdq(1, n);
    printf("%.3lf\n", f[n]);
}

