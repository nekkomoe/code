#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 5e5 + 10;

int read() {
    int x = 0, c = 0;
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
    return x;
}

struct LB {
    int val[31], id[31];
    void ins(int pos, int x) {
        for(int i = 30 ; ~ i ; -- i) {
            if(x & (1 << i)) {
                if(!val[i]) {
                    val[i] = x, id[i] = pos;
                    break;
                } else {
                    if(id[i] < pos) {
                        swap(id[i], pos);
                        swap(val[i], x);
                    }
                    x ^= val[i];
                }
            }
        }
    }
    int ask(int pos) {
        int res = 0;
        for(int i = 30 ; ~ i ; -- i) {
            if(id[i] < pos) {
                continue;
            }
            if((res ^ val[i]) > res) {
                res ^= val[i];
            }
        }
        return res;
    }
} lb[N];

int main() {
    int n = read();
    for(int i = 1 ; i <= n ; ++ i) {
        lb[i] = lb[i - 1];
        lb[i].ins(i, read());
    }
    for(int i = read() ; i ; -- i) {
        int l = read(), r = read();
        printf("%d\n", lb[r].ask(l));
    }
}
