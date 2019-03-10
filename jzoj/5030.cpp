#include "bits/stdc++.h"
using namespace std;

int a, b, c, d;

map<vector<int>, bool> mp;
int sol(vector<int> hs) {
    if(mp.count(hs)) return mp[hs];

    // for(int i = 1 ; i <= 4 ; ++ i) {
    //     printf("%d ", hs[i]);
    // } puts("");

    for(int i = 1 ; i <= 4 ; ++ i) {
        if(hs[i] - i >= 0) {
            hs[i] -= i;
            int flag = sol(hs);
            hs[i] += i;
            if(!flag) {
                return mp[hs] = 1;
            }
        }
    }
    for(int i = 2 ; i <= 4 ; ++ i) {
        if(hs[i]) {
            for(int j = 1 ; j < i ; ++ j) {
                int k = i - j;
                vector<int> mem = hs;
                -- hs[i];
                ++ hs[j];
                ++ hs[k];
                int flag = sol(hs);
                hs = mem;
                if(!flag) {
                    return mp[hs] = 1;
                }
            }
        }
    }
    return mp[hs] = 0;
}

int rd2() {
    char c = 0;
    int x = 0;
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = (x * 10 + c - '0') % 2, c = getchar();
    return x;
}

int rd3() {
    char c = 0;
    int x = 0;
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = (x * 10 + c - '0') % 3, c = getchar();
    return x;
}

void runprog() {
    // scanf("%d%d%d%d", &a, &b, &c, &d);
    // vector<int> op;
    // op.push_back(0);
    // op.push_back(a), op.push_back(b), op.push_back(c), op.push_back(d);
    // if(sol(op)) {
    //     puts("1");
    // } else {
    //     puts("0");
    // }

    int a = 0, b = 0, c = 0, d = 0;

    a = rd2();
    b = rd3();
    c = rd2();
    d = rd3();

    int way[3];
    if(a % 2 == 0) {
        // 0 1 1
        // int way[3] = { 0, 1, 1 };
        //             1  0  1
        way[0] = 0, way[1] = 1, way[2] = 1;
    } else {
        // 1 0 1
        // int way[3] = { 1, 0, 1 };

        way[0] = 1, way[1] = 0, way[2] = 1;
    }

    int pos = 0;
    pos = ((pos + b) % 3 + 3) % 3;
    d %= 3;
    pos = ((pos + d) % 3 + 3) % 3;
    if(pos == 2) {
        puts("1");
    } else {
        printf("%d\n", c % 2 == 0 ? way[pos] : !way[pos]);
    }
}

void test() {
    // int a = 2, b = 3;
    
    for(int a = 0 ; a <= 10 ; ++ a) {
        for(int b = 0 ; b <= 0 ; ++ b) {
            printf("a = %d, b = %d\n", a, b);
            vector<int> op(5);
            op[0] = 0;
            op[1] = a, op[2] = b;
            for(int i = 0 ; i <= 10 ; ++ i) {
                for(int j = 0 ; j <= 10 ; ++ j) {
                    op[3] = i, op[4] = j;
                    printf("%d ", sol(op));
                }
                puts("");
            }
            puts("");
        }
    }
}

int main() {
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }

    // test();
}
