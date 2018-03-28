// 平衡树

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>

using namespace std;

const int N = 2e5 + 10;

int n, m, q, a[N], b[N];

int ch[N][2], sz[N], tot, val[N], tag[N], root;

int makeNode(int v) {
    tot ++;
    val[tot] = v;
    sz[tot] = 1;
    return tot;
}

void update(int node) {
    node[sz] = node[ch][0][sz] + node[ch][1][sz] + 1;
}

typedef pair<int, int> p;

void push(int node) {
    if(node[tag]) {
        swap(node[ch][0], node[ch][1]);
        node[ch][0][tag] ^= 1;
        node[ch][1][tag] ^= 1;
        node[tag] ^= 1;
    }
}

p split(int node, int k) {
    push(node);
    if(!node) {
        return p(0, 0);
    }
    if(node[ch][0][sz] >= k) {
        p ret = split(node[ch][0], k);
        node[ch][0] = ret.second;
        ret.second = node;
        update(node);
        return ret;
    } else {
        p ret = split(node[ch][1], k - node[ch][0][sz] - 1);
        node[ch][1] = ret.first;
        ret.first = node;
        update(node);
        return ret;
    }
}

int merge(int nodeA, int nodeB) {
    if(!nodeA || !nodeB) return nodeA | nodeB;
    push(nodeA);
    push(nodeB);
    if(rand() % (nodeA[sz] + nodeB[sz]) < nodeA[sz]) {
        nodeA[ch][1] = merge(nodeA[ch][1], nodeB);
        update(nodeA);
        return nodeA;
    } else {
        nodeB[ch][0] = merge(nodeA, nodeB[ch][0]);
        update(nodeB);
        return nodeB;
    }
}

int main() {
    srand(19260817);
    scanf("%d%d%d", &n, &q, &m);
    for(int i = 1 ; i <= n ; i ++) {
        scanf("%d", &a[i]);
        root = merge(root, makeNode(a[i]));
    }
    for(int i = 1, t, l, r ; i <= q ; i ++) {
        scanf("%d%d%d", &t, &l, &r);
        if(t == 1) {
            p x = split(root, r);
            p y = split(x.first, l - 1);
            p z = split(y.second, r - l);
            root = merge(merge(y.first, merge(z.second, z.first)), x.second);
        } else if(t == 2){
            p x = split(root, r);
            p y = split(x.first, l - 1);
            push(y.second);
            y.second[tag] ^= 1;
            root = merge(merge(y.first, y.second), x.second);
        }
    }
    for(int i = 1 ; i <= m ; i ++) {
        scanf("%d", &b[i]);
        p x = split(root, b[i] - 1);
        p y = split(x.second, 1);
        push(y.first);
        printf("%d ", y.first[val]);
        root = merge(x.first, merge(y.first, y.second));
    }
}
