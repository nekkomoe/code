// 题意：支持如下操作（可以离线）：1. 插入一个整数 2. 删除一个整数 3. 查询当前数集的最大子集异或值
// 题解：线段树分治后，用dfs遍历并进行维护线性基
// 标签：线段树分治，线性基

#include <bits/stdc++.h>

using namespace std;

const int N = 500010;

#define lc (id << 1)

#define rc (id << 1 | 1)

struct T {
    vector<int> v;
    void ins(int x) {
        for(int i = 0 ; i < v.size() ; ++ i) {
            if((x ^ v[i]) < x) x ^= v[i];
        }
        if(x) {
            v.push_back(x);
            for(int i = v.size() - 1 ; i ; -- i) if(v[i] > v[i - 1]) swap(v[i], v[i - 1]); 
        } 
    }
    void clear() {
        v.clear();
    }
    int getmx() {
        int ret = 0;
        for(int i = 0 ; i < v.size() ; ++ i) {
            if((ret ^ v[i]) > ret) {
                ret ^= v[i];
            }
        }
        return ret;
    }
} xxj[N * 10], t;

void modify(int id, int l, int r, int ql, int qr, int val) {
    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) {
        xxj[id].ins(val);
    } else if(l > qr || r < ql) {
        return ;
    } else {
        modify(lc, l, mid, ql, qr, val);
        modify(rc, mid + 1, r, ql, qr, val);
    }
}

map<int, vector<int> > lst;

int n;

void dfs(int id, int l, int r) {
    int mid = (l + r) >> 1;
    for(int i = 0 ; i < xxj[id].v.size() ; ++ i) {
        t.ins(xxj[id].v[i]);
    }
    if(l == r) {
        printf("%d\n", t.getmx());
    } else {
        T tmp = t;
        dfs(lc, l, mid);
        t = tmp;
        dfs(rc, mid + 1, r);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1, x ; i <= n ; ++ i) {
        scanf("%d", &x);
        if(x > 0) {
            lst[x].push_back(i);
        } else {
            x = -x;
            if(lst.find(x) != lst.end()) {
                int l = lst[x].back(), r = i - 1;
                lst[x].pop_back();
                if(lst[x].empty()) lst.erase(x);
                modify(1, 1, n, l, r, x);
            }
        }
    }
    for(map<int, vector<int> > :: iterator it = lst.begin() ; it != lst.end() ; ++ it) {
        modify(1, 1, n, it -> second[0], n, it -> first);
    }
    dfs(1, 1, n);
}
