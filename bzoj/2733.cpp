#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <list>
  
using namespace std;
  
const int N = 100010;
  
int n, m, q, x, y, id[N];
char op[10];
  
int GC[N], gcp;
  
int keys[N], hd[N], nxt[N], lst[N];
  
int root[N], ch[N * 20][2], sum[N * 20];
  
int New() {
    static int cnt = 0;
    if(gcp) {
        int rt =GC[gcp --];
        if(rt[ch][0]) {
            GC[++ gcp] = rt[ch][0];
        }
        if(rt[ch][1]) {
            GC[++ gcp] = rt[ch][1];
        }
        rt[ch][0] = rt[ch][1] = 0;
        rt[sum] = 0;
        return rt;
    } else {
        return ++ cnt;
    }
}
  
#define walk for(int i = 16, t ; (t = (val >> i) & 1), ~i ; i --)
  
void ins(int rt, int val) {
    walk {
        if(rt[ch][t] == 0) rt[ch][t] = New();
        (rt = rt[ch][t])[sum] ++;
    }
}
  
int kth(int rt, int val) {
    int ret = 0;
    walk {
        if(val > rt[ch][0][sum]) {
            val -= rt[ch][0][sum];
            ret |= 1 << i;
            rt = rt[ch][1];
        } else {
            rt = rt[ch][0];
        }
    }
    return ret;
}
  
int acc[N], size[N];
  
void init(int n) {
    for(int i = 1 ; i <= n ; i ++) {
        i[acc] = i;
        i[size] = 1;
    }
}
  
int find(int x) {
    return x == x[acc] ? x : x[acc] = find(x[acc]);
}
  
void uni(int x, int y) {
    x = find(x);
    y = find(y);
    if(x != y) {
        y[size] += x[size];
        x[acc] = y;
    }
}
  
void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if(x != y) {
        if(x[size] > y[size]) {
            swap(x, y);
        }
        for(int i = x[hd] ; i ; i = nxt[i]) {
            ins(y, keys[i]);
            if(nxt[i] == 0) {
                y[lst][nxt] = x;
                y[lst] = x[lst];
            }
        }
        GC[++ gcp] = x;
        uni(x, y);
    }
}
  
int ask(int rt, int k) {
    rt = find(rt);
    if(rt[size] < k) {
        return -1;
    } else {
        int res = kth(rt, k);
        return res[id];
    }
}
  
int main() {
    scanf("%d%d", &n, &m);
    init(n);
    for(int i = 1 ; i <= n ; i ++) {
        i[root] = New();
    }
    for(int i = 1 ; i <= n ; i ++) {
        scanf("%d", &x);
        x[id] = i;
        ins(i[root], x);
        i[keys] = x;
        i[hd] = i;
        i[lst] = i;
    }
    for(int i = 1 ; i <= m ; i ++) {
        scanf("%d%d", &x, &y);
        merge(x, y);
    }
    scanf("%d", &q);
    for(int i = 1 ; i <= q ; i ++) {
        scanf("%s%d%d", op, &x, &y);
        if(op[0] == 'B') {
            merge(x, y);
        } else {
            printf("%d\n", ask(x, y));
        }
    }
    return 0;
}
