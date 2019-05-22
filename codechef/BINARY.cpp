#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 3e6 + 10;

int n, k, mp[N], len, ans[N], offset, lim;

int getlen() {
    int res = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        if(mp[i] == 0) {
            int tag = 0, tot = 0;
            for(int j = i ; j <= n ; ++ j) {
                if(mp[j] == 1) {
                    ++ tot;
                    res = max(res, (j - i + 1) - tot + tag);
                }
                if(mp[j] == 0) {
                    -- tag;
                } else {
                    ++ tag;
                }
                if(tag < 0) {
                    tag = 0;
                }
            }
            break;
        }
    }
    return res;
}

// // 1. 找到 1 <= j <= len，满足 i - j + 1 == a[offset + 1 + j] + 1
// // 2. 把 a[offset + 1] ~ a[offset + j] 按照 i, i - 1, i - 2, ... 的值填充
// // 3. 把 a[offset + j + 1] ~ a[offset + len] 都 +1
// // 4. ans[a[offset + k + 1]] = 1
// int j = getj(i);
// set_d(1, j, i);
// plus_1(offset + j + 1, offset + len);
// ans[get_val(offset + k + 1)] = 1;

namespace SEGTREE {
    const int T = N * 10;
    int nek[T], d[T]; // 首项，公差
    int val[T], tag[T];
    void init() {
        // memset(nek, -1, sizeof nek);
        // memset(tag, -1, sizeof tag);
        for(int i = 1 ; i <= lim * 10 ; ++ i) {
            nek[i] = tag[i] = -1;
            d[i] = 0;
            val[i] = 0;
        }
    }

    #define lc (id << 1)
    #define rc (id << 1 | 1)

    void push(int id, int l, int r) {
        if(nek[id] != -1) {
            int mid = (l + r) >> 1;
            val[id] = nek[id];
            // printf("val[%d][%d, %d] = %d\n", id, l, r, nek[id]);
            
            nek[lc] = nek[id], d[lc] = d[id];
            nek[rc] = (mid - l + 1) * d[id] + nek[id], d[rc] = d[id];
            tag[lc] = tag[rc] = -1;

            // printf("%d, %d\n", nek[lc], d[lc]);
            // printf("%d, %d\n", nek[rc], d[rc]);

            nek[id] = -1, d[id] = 0;
        }
        if(tag[id] != -1) {
            val[id] += tag[id];
            if(tag[lc] == -1) tag[lc] = tag[id];
            else tag[lc] += tag[id];
            if(tag[rc] == -1) tag[rc] = tag[id];
            else tag[rc] += tag[id];
            tag[id] = -1;
        }
    }

    int ask(int id, int l, int r, int pos) {
        int mid = (l + r) >> 1;
        push(id, l, r);
        if(l == r) {
            return val[id];
        } else if(pos <= mid) {
            return ask(lc, l, mid, pos);
        } else {
            return ask(rc, mid + 1, r, pos);
        }
    }

    int getj(int val) {
        int l = 1, r = len, res = 1;
        while(l <= r) {
            int mid = (l + r) >> 1;
            int tmp = ask(1, 1, lim, offset + 1 + mid);
            // printf("%d - %d >= %d\n", val, mid, tmp);
            if(val - mid == tmp) {
                res = mid;
                r = mid - 1;
            } else if(val - mid > tmp) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return res;
    }

    void set_d(int id, int l, int r, int ql, int qr, int shou_xiang, int gong_cha) {
        // assert(shou_xiang >= 0);
        // printf("[%d, %d] [%d, %d]\n", l, r, ql, qr);
        // printf("(%d, %d)\n", shou_xiang, gong_cha);
        int mid = (l + r) >> 1;
        push(id, l, r);
        if(ql <= l && r <= qr) {
            // printf("end\n");
            if(nek[id] == -1) nek[id] = shou_xiang, d[id] = gong_cha;
            else nek[id] += shou_xiang, d[id] += gong_cha;
            tag[id] = -1;
        } else if(qr <= mid) {
            set_d(lc, l, mid, ql, qr, shou_xiang, gong_cha);
        } else if(ql >= mid + 1) {
            set_d(rc, mid + 1, r, ql, qr, shou_xiang, gong_cha);
        } else {
            set_d(lc, l, mid, ql, mid, shou_xiang, gong_cha);
            int new_shou_xiang = shou_xiang + (mid - ql + 1) * gong_cha;
            // printf("new = %d\n", new_shou_xiang);
            set_d(rc, mid + 1, r, mid + 1, qr, new_shou_xiang, gong_cha);
        }
    }

    void plus_1(int id, int l, int r, int ql, int qr) {
        int mid = (l + r) >> 1;
        push(id, l, r);
        if(ql <= l && r <= qr) {
            if(tag[id] == -1) tag[id] = 1;
            else ++ tag[id];
        } else if(qr <= mid) {
            plus_1(lc, l, mid, ql, qr);
        } else if(ql >= mid + 1) {
            plus_1(rc, mid + 1, r, ql, qr);
        } else {
            plus_1(lc, l, mid, ql, mid);
            plus_1(rc, mid + 1, r, mid + 1, qr);
        }
    }
}

ll a[N];
int getj(int i) {
    // int res = 1;
    // for(int k = 1 ; k <= len ; ++ k) {
    //     if(a[offset + 1 + k] + 1 == i - k + 1) {
    //         res = k;
    //         break;
    //     }
    // }
    // return res;
    return SEGTREE :: getj(i);
}
void set_d(int l, int r, int i, int gc) {
    // for(int j = l ; j <= r ; ++ j) {
    //     a[j] = i;
    //     i += gc;
    // }
    // printf("so = %d, gc = %d\n", i, gc);
    SEGTREE :: set_d(1, 1, lim, l, r, i, gc);
}
void plus_1(int l, int r) {
    // for(int j = l ; j <= r ; ++ j) {
    //     a[j] ++;
    // }
    SEGTREE :: plus_1(1, 1, lim, l, r);
}
int get_val(int pos) {
    // return a[pos];
    return SEGTREE :: ask(1, 1, lim, pos);
}

void nekdeal() {
    offset = len + 10;
    lim = 2 * (len + 20);

    for(int i = 1 ; i <= n ; ++ i) {
        if(mp[i] == 0) {
            continue;
        }
        int t = i;
        -- offset;
        // [offset + 1, offset + len]

        // 1. 找到 1 <= j <= len，满足 i - j + 1 == a[offset + 1 + j] + 1
        // 2. 把 a[offset + 1] ~ a[offset + j] 按照 i, i - 1, i - 2, ... 的值填充
        // 3. 把 a[offset + j + 1] ~ a[offset + len] 都 +1
        // 4. ans[a[offset + k + 1]] = 1
        int j = getj(i);

        // printf("j = %d\n", j);
        // for(int j = 1 ; j <= len ; ++ j) {
        //     printf("%d ", get_val(offset + 1 + j));
        // } puts("");

        set_d(offset + 1, offset + j, i, -1);
        // printf("len = %d\n", len);
        // printf("[%d, %d]\n", offset + j + 1, offset + len);
        if(offset + j + 1 <= offset + len) {
            plus_1(offset + j + 1, offset + len);
        }
        ans[get_val(offset + k + 1)] = 1;

        // for(int j = 1 ; j <= len ; ++ j) {
        //     printf("%d ", get_val(offset + j));
        // } puts("");
    }
    // set_d(1, lim, 0, 0);
    SEGTREE :: init();
}

void runprog() {
    scanf("%d%d", &n, &k);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &mp[i]);
        ans[i] = 0;
    }
    len = getlen();
    k = min(k, len);
    ++ len;
    nekdeal();
    for(int i = 1 ; i <= n ; ++ i) {
        printf("%d ", ans[i]);
    } puts("");
}

int main() {
    SEGTREE :: init();
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}

/*
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 3e6 + 10;

int n, k, mp[N], len, ans[N], offset;

int getlen() {
    int res = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        if(mp[i] == 0) {
            int tag = 0, tot = 0;
            for(int j = i ; j <= n ; ++ j) {
                if(mp[j] == 1) {
                    ++ tot;
                    res = max(res, (j - i + 1) - tot + tag);
                }
                if(mp[j] == 0) {
                    -- tag;
                } else {
                    ++ tag;
                }
                if(tag < 0) {
                    tag = 0;
                }
            }
            break;
        }
    }
    return res;
}

// // 1. 找到 1 <= j <= len，满足 i - j + 1 == a[offset + 1 + j] + 1
// // 2. 把 a[offset + 1] ~ a[offset + j] 按照 i, i - 1, i - 2, ... 的值填充
// // 3. 把 a[offset + j + 1] ~ a[offset + len] 都 +1
// // 4. ans[a[offset + k + 1]] = 1
// int j = getj(i);
// set_d(1, j, i);
// plus_1(offset + j + 1, offset + len);
// ans[get_val(offset + k + 1)] = 1;


ll a[N];
int getj(int i) {
    int res = 1;
    for(int k = 1 ; k <= len ; ++ k) {
        if(a[offset + 1 + k] + 1 == i - k + 1) {
            res = k;
            break;
        }
    }
    return res;
}
void set_d(int l, int r, int i, int gc) {
    for(int j = l ; j <= r ; ++ j) {
        a[j] = i;
        i -= gc;
    }
}
void plus_1(int l, int r) {
    for(int j = l ; j <= r ; ++ j) {
        a[j] ++;
    }
}
int get_val(int pos) {
    return a[pos];
}

void nekdeal() {
    offset = len + 10;

    for(int i = 1 ; i <= n ; ++ i) {
        if(mp[i] == 0) {
            continue;
        }
        int t = i;
        -- offset;
        // [offset + 1, offset + len]


        // 1. 找到 1 <= j <= len，满足 i - j + 1 == a[offset + 1 + j] + 1
        // 2. 把 a[offset + 1] ~ a[offset + j] 按照 i, i - 1, i - 2, ... 的值填充
        // 3. 把 a[offset + j + 1] ~ a[offset + len] 都 +1
        // 4. ans[a[offset + k + 1]] = 1
        int j = getj(i);
        set_d(offset + 1, offset + j, i, 1);
        plus_1(offset + j + 1, offset + len);
        ans[get_val(offset + k + 1)] = 1;
    }
    // printf("offset = %d\n", offset);
    set_d(1, 2 * (len + 20), 0, 0);
}

void runprog() {

    // init();

    scanf("%d%d", &n, &k);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &mp[i]);
        ans[i] = 0;
    }
    len = getlen();
    k = min(k, len);
    ++ len;
    nekdeal();
    for(int i = 1 ; i <= n ; ++ i) {
        printf("%d ", ans[i]);
    } puts("");
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
*/

/*
#include "bits/stdc++.h"
using namespace std;

int main() {
    srand((unsigned long long) new char);
    int t = 1;
    printf("%d\n", t);
    while(t --) {
        int n = 1e6;
        int k = rand() % n + 1;
        printf("%d %d\n", n, k);
        for(int i = 1 ; i <= n ; ++ i) {
            printf("%d ", rand() % 2);
        }
        puts("");
    }
}
*/
