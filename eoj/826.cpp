#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
const int mod = 1e9 + 7;

int n, m, x[N], y[N];

namespace MN_CIR_COV {
    const int N = 1e5 + 10;
    typedef long double DB;
    struct node {
        DB x, y;
    } a[N], O;
    DB r;
    int n;
    inline DB power(DB x)
    {
        return x*x;
    }
    inline DB dis(node a,node b)
    {
        return sqrt(power(a.x-b.x)+power(a.y-b.y));
    }
    inline bool in_circle(node a)
    {
        return dis(a,O)<=r?1:0;
    }
    inline void calc(DB a,DB b,DB c,DB d,DB e,DB f)
    {
        O.x=(b*f-d*e)/(b*c-a*d);
        O.y=(c*e-a*f)/(b*c-a*d);
    }
    inline DB min_cover_circle()
    {
        r = 0;
        register int i,j,k;
        random_shuffle(a+1,a+n+1);
        for (i=1;i<=n;++i)
        if (!in_circle(a[i]))
        {
            O=a[i]; r=0;
            for (j=1;j<i;++j)
            if (!in_circle(a[j]))
            {
                O.x=(a[i].x+a[j].x)/2.0; O.y=(a[i].y+a[j].y)/2.0; r=dis(a[i],O);
                for (k=1;k<j;++k)
                if (!in_circle(a[k])) calc(a[i].x-a[j].x,a[i].y-a[j].y,a[i].x-a[k].x,a[i].y-a[k].y,
                ((power(a[i].x)-power(a[j].x))-(power(a[j].y)-power(a[i].y)))/2.0,
                ((power(a[i].x)-power(a[k].x))-(power(a[k].y)-power(a[i].y)))/2.0),r=dis(a[i],O);
            }
        }
        return r;
    }
}

ll getR(int l, int r) {
    MN_CIR_COV :: n = 0;
    for(int i = l ; i <= r ; ++ i) {
        MN_CIR_COV :: a[++ MN_CIR_COV :: n] = (MN_CIR_COV :: node) { (double) x[i], (double) y[i] };
    }
    return (ll) MN_CIR_COV :: min_cover_circle();
}

int main() {
    srand((unsigned long long) new char);
    // freopen("circle.in", "r", stdin);
    // freopen("circle.out", "w", stdout);
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d%d", &x[i], &y[i]);
    }
    vector<ll> vals;
    int flag = 0;
    ll ans = 0;
    scanf("%d", &m);
    for(int i = 1 ; i <= m ; ++ i) {
        // if(i == 6) break;
        int l, r;
        scanf("%d%d", &l, &r);
        if(flag) {
            printf("%lld\n", (ll) l * r);
        } else {
            vals.push_back(getR(l, r));
            // printf("(%d,%d): R = %lld\n", l, r, getR(l, r));
            ll sum = 1;
            for(int i = 0 ; i < vals.size() ; ++ i) {
                for(int j = i + 1 ; j < vals.size() ; ++ j) {
                    sum = sum * (vals[j] - vals[i]) % mod;
                }
            }
            sum = (sum % mod + mod) % mod;
            if(!sum) {
                flag = 1;
            }
            ll res = (ll) l * r + sum;
            printf("%lld\n", res);
        }
    }
}
