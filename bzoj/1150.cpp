//堆 贪心 用堆模拟费用流退流过程

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>

using namespace std;

const int N = 1e5 + 10;

int val[N], pre[N], sub[N], n, m, ans;;

priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; i ++) {
        scanf("%d", &val[i]);
        pre[i] = i - 1;
        sub[i] = i + 1;
    }
    for(int i = n ; i >= 1 ; i --) {
        val[i] -= val[i - 1];
    }
    for(int i = 2 ; i <= n ; i ++) {
        q.push(make_pair(val[i], i));
    }
    pre[2] = sub[n] = 0;
    for(int i = 1 ; i <= m ; i ++) {
        while(q.top().first != val[q.top().second]) {
            q.pop();
        }
        int x = q.top().second, l = pre[x], r = sub[x];
        ans += val[x];
        q.pop();
        pre[sub[x] = sub[r]] = x;
        sub[pre[x] = pre[l]] = x;
        val[x] = l && r ? min(0x3f3f3f3f, val[l] + val[r] - val[x]) : 0x3f3f3f3f;
        val[l] = val[r] = 0x3f3f3f3f;
        q.push(make_pair(val[x], x));
    }
    printf("%d\n", ans);
}
