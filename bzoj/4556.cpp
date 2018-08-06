// 题意：多次询问s[a..b]的所有子串和s[c..d]的最长公共前缀的最大值
// 题解：后缀树上二分，用主席树check
// 标签：后缀数组，后缀树，后缀自动机

#include <bits/stdc++.h>

using namespace std;

const int N = 100010 * 2;

const int M = 4000005;

int pre[N], ch[N][30], len[N], last = 1, cnt = 1;

int fa[N][30], tmp[N], bak[N], pos[N], n, m;

char s[N];
    
int lc[M], rc[M], root[M], tot;

void insert(int x, int pos, int l, int r) {
    if(l == r) return ;
    int mid = (l + r) >> 1;
    if(pos <= mid) insert(lc[x] = ++ tot, pos, l, mid);
    else insert(rc[x] = ++ tot, pos, mid + 1, r);
}

int merge(int x, int y) {
    if(!x || !y) return x | y;
    int z = ++ tot;
    lc[z] = merge(lc[x], lc[y]);
    rc[z] = merge(rc[x], rc[y]);
    return z;
}

int query(int x, int ql, int qr, int l, int r) {
    if(!x) return 0;
    if(ql <= l && r <= qr) return 1;
    if(l > qr || r < ql) return 0;
    int mid = (l + r) >> 1;
    return query(lc[x], ql, qr, l, mid) || query(rc[x], ql, qr, mid + 1, r);
}

int nd(int l) {
    return len[++ cnt] = l, cnt;
}

void ins(int c, int i) { 
    int p, np, q, nq;
    pre[last = np = nd(len[p = last] + 1)] = 1;
    
    insert(root[np] = ++ tot, i, 1, n);
    pos[i] = np;
    
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    if(p) {
        pre[np] = q = ch[p][c];
        if(len[p] + 1 != len[q]) {
            nq = nd(len[p] + 1);
            memcpy(ch[nq], ch[q], sizeof ch[q]);
            pre[nq] = pre[q], pre[q] = pre[np] = nq;
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    }
}

void build() {
    reverse(s + 1, s + 1 + n);
    for(int i = 1 ; i <= n ; ++ i) ins(s[i] - 'a', i);
    for(int i = 1 ; i <= cnt ; ++ i) fa[i][0] = pre[i];
    for(int j = 1 ; j <= 25 ; ++ j) for(int i = 1 ; i <= cnt ; ++ i) fa[i][j] = fa[fa[i][j - 1]][j - 1];
    
    
    for(int i = 1 ; i <= cnt ; ++ i) tmp[len[i]] ++;
    for(int i = 1 ; i <= cnt ; ++ i) tmp[i] += tmp[i - 1];
    for(int i = 1 ; i <= cnt ; ++ i) bak[tmp[len[i]] --] = i;
    for(int i = cnt ; i ; -- i) {
        int x = bak[i];
        root[pre[x]] = merge(root[pre[x]], root[x]);
    }
    
}

int check(int mid, int x, int l, int r) {
    for(int i = 25 ; ~ i ; -- i) if(len[fa[x][i]] >= mid) x = fa[x][i];
    return query(root[x], l, r, 1, n);
}

void sol(int a, int b, int c, int d) {
    a = n - a + 1, b = n - b + 1, c = n - c + 1, d = n - d + 1;
    swap(a, b), swap(c, d);
    int l = 0, r = min(d - c + 1, b - a + 1);
    while(l < r) {
        int mid = (l + r) / 2 + 1;
        if(check(mid, pos[d], a + mid - 1, b)) l = mid;
        else r = mid - 1;
    }
    printf("%d\n", l);
}

int main() {
    
    freopen("data.in", "r", stdin);
    
    scanf("%d%d%s", &n, &m, s + 1);
    build();
    for(int i = 1, a, b, c, d ; i <= m ; ++ i) {
        scanf("%d%d%d%d", &a, &b, &c, &d), sol(a, b, c, d);
    }
}
