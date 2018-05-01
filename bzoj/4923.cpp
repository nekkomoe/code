#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 1e5 + 10;

int n, m;

int ch[N][2], sz[N], val[N], tag[N], fix[N], root;

int nd(int x) {
    static int tot = 0;
    return val[++ tot] = x, sz[tot] = 1, tot;
}

void push(int x) {
    if(x && tag[x]) {
        val[x] += tag[x];
        tag[ch[x][0]] += tag[x], tag[ch[x][1]] += tag[x];
        tag[x] = tag[0] = 0;
    }
}

void update(int x) {
    if(x) {
        sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + 1;
    }
}

int merge(int x, int y) {
    push(x), push(y);
    if(!x || !y) return x | y;
    if(fix[x] < fix[y]) {
        ch[x][1] = merge(ch[x][1], y);
        return update(x), x;
    } else {
        ch[y][0] = merge(x, ch[y][0]);
        return update(y), y;
    }
}

typedef pair<int, int> p;

p split(int x, int k) {
    p res;
    push(x);
    if(!x) return res;
    if(sz[ch[x][0]] >= k) {
        res = split(ch[x][0], k);
        ch[x][0] = res.second, res.second = x;
    } else {
        res = split(ch[x][1], k - sz[ch[x][0]] - 1);
        ch[x][1] = res.first, res.first = x;
    }
    return update(x), res;
}

int le(int x, int k) {
    push(x);
    if(!x) return 0;
    if(val[x] <= k) return sz[ch[x][0]] + 1 + le(ch[x][1], k);
    return le(ch[x][0], k);
}

void ins(int &x, int y) {
    p t = split(x, le(x, val[y]));
    x = merge(merge(t.first, y), t.second);
}

int seq[N], tp;

void dfs(int x) {
    if(x) {
        push(x);
        dfs(ch[x][0]);
        seq[++ tp] = x;
        dfs(ch[x][1]);
        ch[x][0] = ch[x][1] = 0, sz[x] = 1;
    }
}

int main() {
    srand((unsigned long long) new char);
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) fix[i] = i; random_shuffle(fix + 1, fix + 1 + n);
    for(int i = 1, x ; i <= n ; ++ i) {
        scanf("%d", &x);
        ins(root, nd(x));
    }
    for(int i = 1, op, k ; i <= m ; ++ i) {
        scanf("%d%d", &op, &k);
        if(op == 1) {
            p x = split(root, k - 1);
            p y = split(x.second, 1);


            push(y.first), printf("%d\n", val[y.first]);
            root = merge(x.first, merge(y.first, y.second));

        } else {
            // [k + 1, 2k]
            p x = split(root, le(root, 2 * k));
            p y = split(x.first, le(x.first, k));
            tp = 0, dfs(y.second);
            for(int i = 1 ; i <= tp ; ++ i) {
                val[seq[i]] -= k;
                ins(y.first, seq[i]);
            }

            // [2k + 1, inf]
            tag[x.second] -= k;

            root = merge(y.first, x.second);
        }
    }
}

