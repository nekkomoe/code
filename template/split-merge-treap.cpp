#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
 
#ifdef ONLINE_JUDGE
    #define debug
#else
    #define debug printf("passing [%s] in line %d\n", __FUNCTION__, __LINE__)
#endif
 
using namespace std;
 
typedef long long ll;
 
typedef pair<int, int> p;
 
const int N = 100010;
 
int val[N], tag[N], ch[N][2], sz[N], tot;
 
int nn(int v) {
    ++ tot;
    tot[val] = v;
    tot[sz] = 1;
    return tot;
}
 
void push(int x) {
    if(tag[x]) {
        swap(x[ch][0], x[ch][1]);
        x[ch][0][tag] ^= 1;
        x[ch][1][tag] ^= 1;
        x[tag] = 0;
    }
}
 
void update(int x) {
    x[sz] = x[ch][0][sz] + x[ch][1][sz] + 1;
}
 
int merge(int a, int b) {
    push(a), push(b);
    if(!a || !b) return a | b;
    if(rand() % (a[sz] + b[sz]) < a[sz]) {
        a[ch][1] = merge(a[ch][1], b);
        update(a);
        return a;
    } else {
        b[ch][0] = merge(a, b[ch][0]);
        update(b);
        return b;
    }
}
 
p split(int x, int k) {
    push(x);
    p ret = p(0, 0);
    if(x) {
        if(x[ch][0][sz] >= k) {
            ret = split(x[ch][0], k);
            x[ch][0] = ret.second;
            ret.second = x;
        } else {
            ret = split(x[ch][1], k - x[ch][0][sz] - 1);
            x[ch][1] = ret.first;
            ret.first = x;
        }
        update(x);
    }
    return ret;
}
 
int n, m, rt;
 
void dfs(int x) {
    push(x);
    if(x) {
        dfs(x[ch][0]);
        printf("%d ", x[val]);
        dfs(x[ch][1]);
    }
}
 
int main() {
    srand((unsigned long long) new char);
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        rt = merge(rt, nn(i));
    }
    for(int i = 1, l, r ; i <= m ; ++ i) {
        scanf("%d%d", &l, &r);
        p p1 = split(rt, r);
        p p2 = split(p1.first, l - 1);
        p2.second[tag] ^= 1;
        rt = merge(merge(p2.first, p2.second), p1.second);
    }
    dfs(rt);
}
