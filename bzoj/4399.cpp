#include <bits/stdc++.h>
using namespace std;
const int N = 3e6 + 10;

int m;

struct Q {
    int ops;
    int a, b, x, k;
} q[int(5e5) + 10];

/*
若c=1，之后一个正整数x，表示新建一个权值为x的节点，并且节点编号为n+1（当前有n个节点）。
若c=2，之后两个正整数a，b，表示在a，b之间连接一条边。
若c=3，之后两个正整数a，x，表示a联通快内原本权值小于x的节点全部变成x。
若c=4，之后两个正整数a，x，表示a联通快内原本权值大于x的节点全部变成x。
若c=5，之后两个正整数a，k，表示询问a所属于的联通块内的第k小的权值是多少。
若c=6，之后两个正整数a，b，表示询问a所属联通快内所有节点权值之积与b所属联通快内所有节点权值之积的大小，
若a所属联通快内所有节点权值之积大于b所属联通快内所有节点权值之积，输出1，否则为0。
若c=7，之后一个正整数a，表示询问a所在联通块大小
*/

vector<int> num;
int rev[N], lim;
double tlg[N];
int getval(int x) {
    return lower_bound(num.begin(), num.end(), x) - num.begin() + 1;
}

int n, tot;
int sz[N], lc[N], rc[N];
double mul[N];

int merge(int x, int y) {
    if(!x || !y) {
        return x | y;
    }
    lc[x] = merge(lc[x], lc[y]);
    rc[x] = merge(rc[x], rc[y]);
    mul[x] += mul[y];
    sz[x] += sz[y];
    return x;
}

int dfs(int &x, int l, int r, int ql, int qr) {
    int mid = (l + r) >> 1;
    if(!x || qr < l || ql > r) {
        return 0;
    }
    if(ql <= l && r <= qr) {
        int res = sz[x];
        x = 0;
        return res;
    } else {
        int res = dfs(lc[x], l, mid, ql, qr) + dfs(rc[x], mid + 1, r, ql, qr);
        sz[x] = sz[lc[x]] + sz[rc[x]];
        mul[x] = mul[lc[x]] + mul[rc[x]];
        return res;
    }
}

int getkth(int x, int l, int r, int k) {
    int mid = (l + r) >> 1;
    if(!x) {
        return -1;
    }
    if(l == r) {
        return rev[l];
    }
    if(sz[lc[x]] >= k) {
        return getkth(lc[x], l, mid, k);
    } else {
        return getkth(rc[x], mid + 1, r, k - sz[lc[x]]);
    }
}

void modify(int &x, int l, int r, int pos, int val) {
    if(!x) {
        x = ++ tot;
    }
    int mid = (l + r) >> 1;
    if(l == r) {
        sz[x] = val;
        mul[x] = val * tlg[l];
        return ;
    } else if(pos <= mid) {
        modify(lc[x], l, mid, pos, val);
    } else {
        modify(rc[x], mid + 1, r, pos, val);
    }
    sz[x] = sz[lc[x]] + sz[rc[x]];
    mul[x] = mul[lc[x]] + mul[rc[x]];
}

int rt[int(5e5) + 10];
int fa[int(5e5) + 10];
int get(int x) {
    return x == fa[x] ? x : fa[x] = get(fa[x]);
}

int main() {
    scanf("%d", &m);
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%d", &q[i].ops);
        switch(q[i].ops) {
            case 1:
                scanf("%d", &q[i].x);
                num.push_back(q[i].x);
                break;
            case 2:
                scanf("%d%d", &q[i].a, &q[i].b);
                break;
            case 3:
                scanf("%d%d", &q[i].a, &q[i].x);
                num.push_back(q[i].x);
                break;
            case 4:
                scanf("%d%d", &q[i].a, &q[i].x);
                num.push_back(q[i].x);
                break;
            case 5:
                scanf("%d%d", &q[i].a, &q[i].k);
                break;
            case 6:
                scanf("%d%d", &q[i].a, &q[i].b);
                break;
            case 7:
                scanf("%d", &q[i].a);
                break;
            default:
                break;
        }
    }
    sort(num.begin(), num.end());
    num.erase(unique(num.begin(), num.end()), num.end());
    lim = num.size();
    for(int i = 0 ; i < num.size() ; ++ i) {
        rev[i + 1] = num[i];
        tlg[i + 1] = log(num[i]);
    }

    /*
    若c=1，之后一个正整数x，表示新建一个权值为x的节点，并且节点编号为n+1（当前有n个节点）。
    若c=2，之后两个正整数a，b，表示在a，b之间连接一条边。
    若c=3，之后两个正整数a，x，表示a联通快内原本权值小于x的节点全部变成x。
    若c=4，之后两个正整数a，x，表示a联通快内原本权值大于x的节点全部变成x。
    若c=5，之后两个正整数a，k，表示询问a所属于的联通块内的第k小的权值是多少。
    若c=6，之后两个正整数a，b，表示询问a所属联通快内所有节点权值之积与b所属联通快内所有节点权值之积的大小，
    若a所属联通快内所有节点权值之积大于b所属联通快内所有节点权值之积，输出1，否则为0。
    若c=7，之后一个正整数a，表示询问a所在联通块大小
    */


    for(int i = 1 ; i <= m ; ++ i) {
        int x, a, b, k, res;
        switch(q[i].ops) {
            case 1:
                x = getval(q[i].x);
                ++ n, fa[n] = n;
                modify(rt[n], 1, lim, x, 1);
                break;
            case 2:
                a = get(q[i].a), b = get(q[i].b);
                if(a != b) {
                    fa[b] = a;
                    rt[a] = merge(rt[a], rt[b]);
                }
                break;
            case 3:
                a = get(q[i].a), x = getval(q[i].x);
                res = dfs(rt[a], 1, lim, 1, x);
                modify(rt[a], 1, lim, x, res);
                // printf("res = %d\n", res);
                break;
            case 4:
                a = get(q[i].a), x = getval(q[i].x);
                res = dfs(rt[a], 1, lim, x, lim);
                modify(rt[a], 1, lim, x, res);
                break;
            case 5:
                a = get(q[i].a), k = q[i].k;
                printf("%d\n", getkth(rt[a], 1, lim, k));
                break;
            case 6:
                a = get(q[i].a), b = get(q[i].b);
                printf("%d\n", mul[rt[a]] > mul[rt[b]]);
                break;
            case 7:
                a = get(q[i].a);
                printf("%d\n", sz[rt[a]]);
                break;
            default:
                break;
        }
    }
}
