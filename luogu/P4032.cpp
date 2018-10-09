#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;
 
const int N = 100010;
 
int n, q, s[N], cnt[N];
//              锅里某种食物个数
 
// 区间熟了的元素个数
namespace bit {
    int a[N];
    void add(int i) {
        for( ; i <= n ; i += i & -i) ++ a[i];
    }
    void del(int i) {
        for( ; i <= n ; i += i & -i) -- a[i];
    }
    int sum(int i) {
        int ret = 0;
        for( ; i ; i -= i & -i) ret += a[i];
        return ret;
    }
    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};
 
map<int, int> glo; // 熟了的元素的个数
 
struct T {
    int id;               // 编号
    long long finishTime; // 完成时间点
};
 
// 剩余时间小的放上面
bool operator < (T x, T y) {
    return x.finishTime > y.finishTime;
}
 
priority_queue<T> hp; // 未熟的元素
 
priority_queue<T> mn[N]; // 每种未熟的元素
 
void reset() {
    glo.clear();
    while(hp.size()) hp.pop();
    memset(bit :: a, 0, sizeof bit :: a);
    memset(cnt, 0, sizeof cnt);
    for(int i = 1 ; i <= n ; ++ i) {
        while(mn[i].size()) {
            mn[i].pop();
        }
    }
}
 
void sol() {
    scanf("%d", &n);
    reset();
 
    long long tot = 0; // 已经度过的时间
 
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &s[i]);
    scanf("%d", &q);
    for(int i = 1, t, op, id, l, r ; i <= q ; ++ i) {
        scanf("%d%d", &t, &op);
         
        tot = t;
 
        // 处理熟了的元素
        while(hp.size() && hp.top().finishTime <= tot) {
            T x = hp.top();
            hp.pop();
            mn[x.id].pop();
            bit :: add(x.id);
            ++ glo[x.id];
        }
 
        if(op == 0) {
            // 新东西被加入
            scanf("%d", &id);
            hp.push((T) {id, tot + s[id]});
            mn[id].push((T) {id, tot + s[id]});
            ++ cnt[id];
        } else if(op == 1) {
            // Yazid 要吃东西
            if(glo.size()) {
                map<int, int> :: iterator it = glo.begin(); // 要吃的那个
                printf("%d\n", it -> first);
                bit :: del(it -> first);
                -- cnt[it -> first];
                if(-- (it -> second) == 0) { // 如果吃完了就删了
                    glo.erase(it);
                }
            } else {
                puts("Yazid is angry.");
            }
        } else if(op == 2) {
            // YJQQQAQ 要吃东西
            scanf("%d", &id);
            if(cnt[id]) {
                map<int, int> :: iterator it = glo.find(id);
                if(it != glo.end()) {
                    bit :: del(it -> first);
                    -- cnt[it -> first];
                    if(-- (it -> second) == 0) { // 如果吃完了就删了
                        glo.erase(it);
                    }
                    puts("Succeeded!");
                } else {
                    printf("%lld\n", mn[id].top().finishTime - tot);
                }
            } else {
                puts("YJQQQAQ is angry.");
            }
        } else if(op == 3) {
            scanf("%d%d", &l, &r);
            printf("%d\n", bit :: sum(l, r));
        }
    }
}
 
int main() {
    // freopen("in", "r", stdin);
    int tc;
    scanf("%d", &tc);
    while(tc --) {
        sol();
    }
}