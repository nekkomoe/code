%:pragma GCC optimize(2)
 
#include <cstdio>
#define lc (id << 1)
#define rc (id << 1 | 1)
 
const int N = 1100000;
 
int n, m;
 
template<class T> inline void read(T &x) {
    x = 0; int f = 0; char ch = getchar();
    while(ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while('0' <= ch && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ '0'), ch = getchar();
    x = f ? -x : x;
}
 
int tag[N]; // tag = 1: 设置0; tag = 2: 设置1; tag = 3: 取反
int sum[N]; // 1的个数
int lmx[N][2]; // 从左端开始往右0/1最长长度
int rmx[N][2]; // 从右端开始往左0/1最长长度
int mx[N][2];  // 最多连续0/1的个数
 
inline void swap(int &a, int &b) {register int c = b; b = a; a = c;}
 
inline int max(int a, int b) {return a > b ? a : b;}
 
inline int min(int a, int b) {return a < b ? a : b;}
 
#define max3(a, b, c) max(a, max(b, c))
 
int d[3];
 
inline void push(int id, int len) {
    if(tag[id]) {
        register int &td = tag[id];
        d[2] = len;
        if(tag[id] <= 2) {
            // 都设成0/1
            sum[id] = d[td];
            lmx[id][0] = rmx[id][0] = mx[id][0] = d[3 - td];
            lmx[id][1] = rmx[id][1] = mx[id][1] = d[td];
            tag[lc] = tag[rc] = td;
        } else {
            // 都取反
            sum[id] = len - sum[id];
            swap(lmx[id][0], lmx[id][1]);
            swap(rmx[id][0], rmx[id][1]);
            swap(mx[id][0], mx[id][1]);
            tag[lc] = 3 - tag[lc];
            tag[rc] = 3 - tag[rc];
        }
        tag[id] = 0;
    }
}
 
void update(int id, int len, int lenl, int lenr) {
    push(lc, lenl), push(rc, lenr);
    sum[id] = sum[lc] + sum[rc];
#define T(i)                                                                            \
        lmx[id][i] = lmx[lc][i];                                                        \
        if(lmx[lc][i] == lenl) lmx[id][i] += lmx[rc][i];                         \
        rmx[id][i] = rmx[rc][i];                                                        \
        if(rmx[rc][i] == lenr) rmx[id][i] += rmx[lc][i];                             \
        mx[id][i] = max3(mx[lc][i], mx[rc][i], rmx[lc][i] + lmx[rc][i]);
    T(0);
    T(1);
}
 
int v;
 
void modify(int id, int l, int r, int ql, int qr) {
    push(id, r - l + 1);
    register int mid = (l + r) >> 1;
    if(l > qr || r < ql) return;
    if(ql <= l && r <= qr) tag[id] = v;
    else modify(lc, l, mid, ql, qr), modify(rc, mid + 1, r, ql, qr), update(id, r - l + 1, mid - l + 1, r - mid);
}
 
struct Q {
    int first, second;
    Q() {}
    Q(int first, int second): first(first), second(second) {}
};
 
Q query(int id, int l, int r, int ql, int qr) {
    push(id, r - l + 1);
    register int mid = (l + r) >> 1;
    if(ql == l && r == qr) {
        return Q(sum[id], mx[id][1]);
    } else if(qr <= mid) {
        return query(lc, l, mid, ql, qr);
    } else if(ql >= mid + 1) {
        return query(rc, mid + 1, r, ql, qr);
    } else {
        register Q r1 = query(lc, l, mid, ql, mid), r2 = query(rc, mid + 1, r, mid + 1, qr);
        push(lc, mid - l + 1), push(rc, r - mid);
        return Q(
                r1.first + r2.first,
                max3(r1.second, r2.second, min(mid - ql + 1, rmx[lc][1]) + min(qr - mid, lmx[rc][1])));
    }
}
 
inline void build(int id, int l, int r, int len) {
    register int mid = (l + r) >> 1, lenl = mid - l + 1, lenr = r - l;
    if(l == r) {
        read(sum[id]);
        lmx[id][sum[id]] = rmx[id][sum[id]] = mx[id][sum[id]] = 1;
    } else {
        build(lc, l, mid, lenl);
        build(rc, mid + 1, r, lenr);
        update(id, len, lenl, lenr);
    }
}
 
int main() {
    read(n), read(m);
    build(1, 1, n, n);
    ++ m;
    register int op, l, r;
    while(-- m) {
        read(op), read(l), read(r);
        if(op == 0) v = 1, modify(1, 1, n, l + 1, r + 1);
        else if(op == 1) v = 2, modify(1, 1, n, l + 1, r + 1);
        else if(op == 2) v = 3, modify(1, 1, n, l + 1, r + 1);
        else if(op == 3) printf("%d\n", query(1, 1, n, l + 1, r + 1).first);
        else if(op == 4) printf("%d\n", query(1, 1, n, l + 1, r + 1).second);
    }
}
