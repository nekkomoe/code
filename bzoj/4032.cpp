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

const int N = 2010 * 2;

struct SAM {
    int len[N], pre[N], ch[N][30], tot, last;
    SAM() { tot = last = 1; }
    int nd(int l) { return len[++ tot] = l, tot; }
    void ins(int c) {
        int p, np, q, nq;
        pre[np = last = nd(len[p = last] + 1)] = 1;
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
} sam;

struct LAM {
    int ch[N][30], last[30];
    void ins(int c, int p) {
        for(int i = 0 ; i < 26 ; ++ i) memcpy(ch[p + 1], last, sizeof last);
        last[c] = p + 1;
    }
} lam;

const int inf = 0x3f3f3f3f;

char a[N], b[N];

int lena, lenb;

int f[N][N];

void cmin(int &x, int y) { x = min(x, y); }

void print(int x) { printf("%d\n", x == inf ? -1 : x); }

void init() {
    for(int i = 1 ; i <= lenb ; ++ i) {
        sam.ins(b[i] - 'a');
    }
    for(int i = lenb ; i ; -- i) {
        lam.ins(b[i] - 'a', i);
    }
    memcpy(lam.ch[1], lam.last, sizeof lam.last);
}

void sol1() {
    int ans = inf;
    for(int i = 1 ; i <= lena ; ++ i) {
        int p = 1;
        for(int j = i ; j <= lena ; ++ j) {
            int c = a[j] - 'a';
            if(sam.ch[p][c]) {
                p = sam.ch[p][c];
            } else {
                cmin(ans, j - i + 1);
                break;
            }
        }
    }
    print(ans);
}

void sol2() {
    int ans = inf;
    for(int i = 1 ; i <= lena ; ++ i) {
        int p = 1;
        for(int j = i ; j <= lena ; ++ j) {
            int c = a[j] - 'a';
            if(lam.ch[p][c]) {
                p = lam.ch[p][c];
            } else {
                cmin(ans, j - i + 1);
                break;
            }
        }
    }
    print(ans);
}

void sol3() {
    memset(f, 0x3f, sizeof f);
    f[0][1] = 0;
    for(int i = 1 ; i <= lena ; ++ i) {
        int c = a[i] - 'a';
        f[i][1] = 0;
        for(int j = 1 ; j <= sam.tot ; ++ j) f[i][j] = f[i - 1][j];
        for(int j = 1 ; j <= sam.tot ; ++ j)
            cmin(f[i][sam.ch[j][c]], min(f[i - 1][sam.ch[j][c]], f[i - 1][j] + 1));
    }
    print(f[lena][0]);
}

void sol4() {
    memset(f, 0x3f, sizeof f);
    f[0][1] = 0;
    for(int i = 1 ; i <= lena ; ++ i) {
        int c = a[i] - 'a';
        f[i][1] = 0;
        for(int j = 1 ; j <= lenb + 1 ; ++ j) f[i][j] = f[i - 1][j];
        for(int j = 1 ; j <= lenb + 1 ; ++ j)
            cmin(f[i][lam.ch[j][c]], min(f[i - 1][lam.ch[j][c]], f[i - 1][j] + 1));
    }
    print(f[lena][0]);
}

int main() {
    scanf("%s%s", a + 1, b + 1);
    lena = strlen(a + 1), lenb = strlen(b + 1);
    init();
    sol1();
    sol2();
    sol3();
    sol4();
}

