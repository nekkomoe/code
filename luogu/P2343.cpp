//平衡树

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cmath>
#include <set>

using namespace std;

const int N = 100010;

int ch[N * 35][2], cnt[N * 35], tot = 1;

#define walk for(int i = 31, bit, rt = 1 ; (bit = ((x >> i) & 1)), i >= 0 ; i --)

void ins(int x) {
    walk {
        if(!ch[rt][bit]) ch[rt][bit] = ++ tot;
        cnt[rt = ch[rt][bit]] ++;
    }
}

int kth(int x) {
    int ret = 0;
    walk {
        if(x > cnt[ch[rt][0]]) x -= cnt[ch[rt][0]], rt = ch[rt][1], ret |= 1 << i;
        else rt = ch[rt][0];
    }
    return ret;
}

int n, q;

int main() {
    scanf("%d%d", &n, &q);
    for(int i = 1, x ; i <= n ; i ++) {
        scanf("%d", &x);
        ins(x);
    }
    for(int i = 1, x, y ; i <= q ; i ++) {
        scanf("%d%d", &x, &y);
        if(x == 1) {
            printf("%d\n", kth(n - y + 1));
        } else {
            n ++;
            ins(y);
        }
    }
}
