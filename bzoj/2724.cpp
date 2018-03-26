#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
const int N = 50010;
 
int f[310][310]; // f[i][j]: 第i块到第j块的众数
 
int cnt[N][310]; // cnt[i][j]: 数字i在前j块中的出现次数
 
int a[N], num[N], id[N], n, m, ans, sz, bel[N], l[N], r[N], tmp[N], len;
 
int main() {
    // freopen("in", "r", stdin);
 
    // read
    scanf("%d%d" ,&n, &m);
    len = (int) sqrt(n) + 1;
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]), num[i] = a[i];
    sort(num + 1, num + 1 + n);
    for(int i = 1, t ; i <= n ; ++ i) {
 
        t = a[i], id[a[i] = lower_bound(num + 1, num + 1 + n, a[i]) - num] = t;
        // id[a[i]] = a[i];
 
        bel[i] = (i - 1) / len + 1;
        l[bel[i]] = l[bel[i]] ? l[bel[i]] : i;
        r[bel[i]] = i;
    }
 
    sz = bel[n];
 
 
    // init cnt
    for(int i = 1 ; i <= n ; ++ i) {
        ++ cnt[a[i]][bel[i]];
    }
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= sz ; ++ j) {
            cnt[i][j] += cnt[i][j - 1];
        }
    }
 
    // init f
    for(int i = 1 ; i <= bel[n] ; ++ i) {
        // 枚举左侧块
        int lb = i, most = 0;
        for(int j = l[i] ; j <= n ; ++ j) {
            // 枚举右块
            int rb = bel[j];
            ++ tmp[a[j]];
            if(tmp[a[j]] > tmp[most] || (tmp[a[j]] == tmp[most] && a[j] < most)) {
                most = a[j];
            }
            f[lb][rb] = most;
        }
        for(int j = l[i] ; j <= n ; ++ j) {
            tmp[a[j]] = 0;
        }
    }
 
    // for(int i = 1 ; i <= sz ; ++ i) {
    //     for(int j = i ; j <= sz ; ++ j) {
    //         printf("most[%d][%d] = %d\n", l[i], r[j], f[i][j]);
    //     }
    // }
 
    // sol
    for(int T = 1, ql, qr ; T <= m ; ++ T) {
        scanf("%d%d", &ql, &qr);
        ql = (ql + ans - 1) % n + 1;
        qr = (qr + ans - 1) % n + 1;
 
        if(ql > qr) swap(ql, qr);
 
        // printf("asking: [%d, %d]\n", ql, qr);
 
        ans = 0;
 
        // 获取答案
        if(bel[ql] == bel[qr]) {
            // 在同一个块里，则brute force
            for(int i = ql ; i <= qr ; ++ i) {
                ++ tmp[a[i]];
                if(tmp[a[i]] > tmp[ans] || (tmp[a[i]] == tmp[ans] && a[i] < ans)) {
                    ans = a[i];
                }
            }
            for(int i = ql ; i <= qr ; ++ i) {
                tmp[a[i]] = 0;
            }
        } else {
            // printf("in diff: ");
 
            int bak = 0;
            // 将已经统计过的计算答案
            if(bel[ql] + 1 <= bel[qr] - 1) {
                bak = ans = f[bel[ql] + 1][bel[qr] - 1];
            }
 
            // 计算未统计过的出现次数
            if(bel[ql] + 1 <= bel[qr] - 1) {
                for(int i = ql ; i <= r[bel[ql]] ; ++ i) {
                    // printf("a[%d] = %d\n", i, a[i]);
                    if(tmp[a[i]]) continue;
                    tmp[a[i]] = cnt[a[i]][bel[qr] - 1] - cnt[a[i]][bel[ql]];
                }
                for(int i = l[bel[qr]] ; i <= qr ; ++ i) {
                    // printf("a[%d] = %d\n", i, a[i]);
                    if(tmp[a[i]]) continue;
                    tmp[a[i]] = cnt[a[i]][bel[qr] - 1] - cnt[a[i]][bel[ql]];
                }
            }
            for(int i = ql ; i <= r[bel[ql]] ; ++ i) {
                // printf("a[%d] = %d\n", i, a[i]);
                ++ tmp[a[i]];
            }
            for(int i = l[bel[qr]] ; i <= qr ; ++ i) {
                // printf("a[%d] = %d\n", i, a[i]);
                ++ tmp[a[i]];
            }
            if(bel[ql] + 1 <= bel[qr] - 1 && !tmp[ans]) {
                tmp[ans] = cnt[ans][bel[qr] - 1] - cnt[ans][bel[ql]];
            }
 
            // 计算为统计过的答案
            for(int i = ql ; i <= r[bel[ql]] ; ++ i) {
                // cout << a[i] << ' ' << tmp[a[i]] << endl;
                if(tmp[a[i]] > tmp[ans] || (tmp[a[i]] == tmp[ans] && a[i] < ans)) {
                    ans = a[i];
                }
            }
            for(int i = l[bel[qr]] ; i <= qr ; ++ i) {
                // cout << a[i] << ' ' << tmp[a[i]] << endl;
                if(tmp[a[i]] > tmp[ans] || (tmp[a[i]] == tmp[ans] && a[i] < ans)) {
                    ans = a[i];
                }
            }
 
            // 还原现场
            for(int i = ql ; i <= r[bel[ql]] ; ++ i) {
                tmp[a[i]] = 0;
            }
            for(int i = l[bel[qr]] ; i <= qr ; ++ i) {
                tmp[a[i]] = 0;
            }
            tmp[bak] = 0;
        }
 
        // for(int i = 1 ; i <= n ; ++ i) if(tmp[i]) return puts("ERROR") & 0;
 
        // 输出答案
        printf("%d\n", ans = id[ans]);
    }
}

