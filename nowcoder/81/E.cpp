#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

struct BASE {
    int a[31];
    void ins(int x) {
        for(int i = 30 ; ~ i ; -- i) {
            if((x >> i) & 1) {
                if(!a[i]) {
                    a[i] = x;
                    break;
                }
                x ^= a[i];
            }
        }
    }
    void merge(int *t) {
        for(int i = 30 ; ~ i ; -- i) {
            ins(t[i]);
        }
    }
    int query() {
        int res = 0;
        for(int i = 30 ; ~ i ; -- i) {
            if(res < (res ^ a[i])) {
                res ^= a[i];
            }
        }
        return res;
    }
} bs[N];

int n, a[N], x[N], ans, fa[N], output[N];

int get(int x) {
    return x == fa[x] ? x : fa[x] = get(fa[x]);
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &x[i]);
    for(int i = n ; i ; -- i) {
        int pos = x[i];
        ans = max(ans, a[pos]);
        fa[pos] = pos;
        bs[pos].ins(a[pos]);
        if(fa[pos + 1]) {
            bs[fa[pos] = get(fa[pos + 1])].merge(bs[pos].a);
            ans = max(ans, bs[get(fa[pos + 1])].query());
        }
        if(fa[pos - 1]) {
            bs[get(fa[pos - 1])].merge(bs[get(pos)].a);
            fa[get(pos)] = get(fa[pos - 1]);
            ans = max(ans, bs[get(fa[pos - 1])].query());
        }
        output[i] = ans;
    }
    for(int i = 1 ; i <= n ; ++ i) {
        printf("%d\n", output[i]);
    }
}
