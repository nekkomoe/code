#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int r, c, m;

namespace work1 {
    const int N = 210;
    int p[N][N], val[N][N][1010], cnt[N][N][1010];
    #define get(val, v) (val[x2][y2][v] + val[x1 - 1][y1 - 1][v] - val[x1 - 1][y2][v] - val[x2][y1 - 1][v])
    void sol() {
        for(int i = 1 ; i <= r ; ++ i) {
            for(int j = 1, x ; j <= c ; ++ j) {
                scanf("%d", &p[i][j]);
            }
        }
        for(int k = 0 ; k <= 1000 ; ++ k) {
            for(int i = 1 ; i <= r ; ++ i) {
                for(int j = 1 ; j <= c ; ++ j) {
                    val[i][j][k] = val[i][j - 1][k];
                    cnt[i][j][k] = cnt[i][j - 1][k];
                    if(p[i][j] >= k) val[i][j][k] += p[i][j], ++ cnt[i][j][k];
                }
                for(int j = 1 ; j <= c ; ++ j) {
                    val[i][j][k] += val[i - 1][j][k];
                    cnt[i][j][k] += cnt[i - 1][j][k];
                }
            }
        }
        for(int i = 1, x1, y1, x2, y2 ; i <= m ; ++ i) {
            ll h;
            scanf("%d%d%d%d%lld", &x1, &y1, &x2, &y2, &h);
            if(get(val, 0) < h) {
                puts("Poor QLW");
                continue;
            }
            int l = 0, r = 1001, ans = 1;
            while(l <= r) {
                int mid = (l + r) >> 1;
                if(get(val, mid) > h) l = (ans = mid) + 1;
                else r = mid - 1;
            }
            ans = max(ans, 1);
            int rescnt = get(cnt, ans + 1), resval = get(val, ans + 1);
            h -= resval;
            if(h >= 0) {
                int cnt = h / ans;
                rescnt += cnt;
                h -= cnt * ans;
                if(h > 0) ++rescnt, h -= ans;
            }
            printf("%d\n", rescnt);
        }
    }
}

namespace work2 {
    const int N = 5500010;
    int p[N], tot[N], lc[N], rc[N], rt[N], cnt;
    ll sum[N];
    void add(int now, int last, int l, int r, int pos) {
        while(l < r) {
            int mid = (l + r) >> 1;
            sum[now] = sum[last] + pos;
            tot[now] = tot[last] + 1;
            lc[now] = lc[last], rc[now] = rc[last];
            if(pos <= mid) {
                r = mid;
                lc[now] = ++ cnt, now = lc[now];
                last = lc[last];
            } else {
                l = mid + 1;
                rc[now] = ++ cnt, now = rc[now];
                last = rc[last];
            }
        }
        sum[now] = sum[last] + pos;
        tot[now] = tot[last] + 1;
    }
    int rescnt, resval;
    void query(int ln, int rn, int l, int r, ll h) {
        while(l < r) {
            int mid = (l + r) >> 1;
            ll sm = sum[rn] - sum[ln];
            ll sml = sum[rn[lc]] - sum[ln[lc]];
            ll smr = sum[rn[rc]] - sum[ln[rc]];
            if(smr > h) {
                l = mid + 1;
                ln = ln[rc], rn = rn[rc];
            } else {
                rescnt += tot[rn[rc]] - tot[ln[rc]];
                h -= smr;
                r = mid;
                ln = ln[lc], rn = rn[lc];
            }
        }
        if(h && l) {
            int cnt = h / l;
            rescnt += cnt;
            h -= cnt * l;
            if(h > 0) ++ rescnt, h -= l;
        }
        resval = h;
    }
    void sol() {
        for(int i = 1 ; i <= c ; ++ i) {
            scanf("%d", &p[i]);
            add(rt[i] = ++ cnt, rt[i - 1], 0, 1001, p[i]);
        }
        for(int i = 1, x1, y1, x2, y2 ; i <= m ; ++ i) {
            ll h;
            scanf("%d%d%d%d%lld", &x1, &y1, &x2, &y2, &h);
            int l = 0, r = 1000;
            rescnt = resval = 0;
            query(rt[y1 - 1], rt[y2], 0, 1001, h);
            if(resval > 0) puts("Poor QLW");
            else printf("%d\n", rescnt);
        }
    }
}

int main() {
    scanf("%d%d%d", &r, &c, &m);
    if(r == 1) work2 :: sol();
    else work1 :: sol();
}
