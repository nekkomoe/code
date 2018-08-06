#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <cctype>
#include <bitset>
 
using namespace std;
 
typedef long long ll;
 
const int N = 2e5 + 10;
 
int n;
 
char s[N];
 
int pre[N], len[N], ch[N][30], pos[N], sz[N], tot = 1, last = 1;
 
int nd(int l) { return len[++ tot] = l, tot; }
 
void ins(int c) {
    int p, np, q, nq;
    pre[np = last = nd(len[p = last] + 1)] = 1;
    sz[np] = 1;
    pos[np] = len[np];
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    if(p) {
        pre[np] = q = ch[p][c];
        if(len[p] + 1 != len[q]) {
            nq = nd(len[p] + 1), pre[nq] = pre[q], pre[np] = pre[q] = nq;
            memcpy(ch[nq], ch[q], sizeof ch[q]);
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    }
}
 
int tmp[N], bak[N];
 
int cnt;
 
struct L {
    int l, r, x;
} line[N];
 
bool operator < (L a, L b) {
    return a.x  > b.x;
}
 
int tag[N * 8], a[N];
 
void push(int id) { if(tag[id]) tag[id << 1] = tag[id << 1 | 1] = tag[id], tag[id] = 0; }
 
void modify(int id, int l, int r, int ql, int qr, int x) {
    if(l != r) push(id);
    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) {
        tag[id] = x;
    } else if(!(l > qr || r < ql)) {
        modify(id << 1, l, mid, ql, qr, x), modify(id << 1 | 1, mid + 1, r, ql, qr, x);
    }
}
 
void dfs1(int id, int l, int r) {
    if(l != r) push(id);
    int mid = (l + r) >> 1;
    if(l == r) a[l] = (tag[id] ? line[tag[id]].x - l : 0);
    else dfs1(id << 1, l, mid), dfs1(id << 1 | 1, mid + 1, r);
}
 
void dfs2(int id, int l, int r) {
    if(l != r) push(id);
    int mid = (l + r) >> 1;
    if(l == r) a[l] = (tag[id] ? (a[l] ? min(a[l], line[tag[id]].x) : line[tag[id]].x) : a[l]);
    else dfs2(id << 1, l, mid), dfs2(id << 1 | 1, mid + 1, r);
}
 
int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for(int i = 1 ; i <= n ; ++ i) ins(s[i] - 'a');
    for(int i = 1 ; i <= tot ; ++ i) tmp[len[i]] ++;
    for(int i = 1 ; i <= tot ; ++ i) tmp[i] += tmp[i - 1];
    for(int i = tot ; i ; -- i) bak[tmp[len[i]] --] = i;
    for(int i = tot ; i > 1 ; -- i) {
        int p = bak[i];
        sz[pre[p]] += sz[p];
        pos[pre[p]] = pos[p];
        if(sz[p] == 1) {
            int u, v, l, r;
 
            u = len[p];
 
            v = len[pre[p]] + 1;
 
            l = pos[p] - len[p] + 1;
 
            r = pos[p] - len[pre[p]];
 
            line[++ cnt] = (L) { l, r, r + v };
        }
    }
     
    sort(line + 1, line + 1 + cnt);
     
    for(int i = 1 ; i <= cnt ; ++ i) {
        int l = line[i].l, r = line[i].r;
        modify(1, 1, n, l, r, i);
    }
     
    dfs1(1, 1, n);
 
    // -------
     
    cnt = 0;
 
    for(int i = tot ; i > 1 ; -- i) {
        int p = bak[i];
        if(sz[p] == 1) {
 
            int l, r, x;
 
            l = pos[p] - len[pre[p]];
 
            r = pos[p];
 
            x = len[pre[p]] + 1;
 
            line[++ cnt] = (L) { l, r, x };
        }
    }
 
    memset(tag, 0, sizeof tag);
 
    sort(line + 1, line + 1 + cnt);
     
    for(int i = 1 ; i <= cnt ; ++ i) {
        int l = line[i].l, r = line[i].r;
        modify(1, 1, n, l, r, i);
    }
     
    dfs2(1, 1, n);
 
    for(int i = 1 ; i <= n ; ++ i) printf("%d\n", a[i]);
 
}
