#include "bits/stdc++.h"
using namespace std;

const int N = 2510;

int n, a[N][N];

void YES() {
    puts("MAGIC");
    exit(0);
}

void NO() {
    puts("NOT MAGIC");
    exit(0);
}

#define yes YES()
#define no NO()

bitset<N> f[N];

struct T { int x, y; } p[N * N];

bool operator < (T i, T j) {
    return a[i.x][i.y] < a[j.x][j.y];
}
int top;

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            scanf("%d", &a[i][j]);
            p[++ top] = (T) { i, j };
        }
    }
    sort(p + 1, p + 1 + top);
    // (1)
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            if(a[i][j] != a[j][i]) {
                no;
            }
        }
    }
    // (2)
    for(int i = 1 ; i <= n ; ++ i) {
        if(a[i][i]) {
            no;
        }
    }
    // (3)
    for(int i = 1 ; i <= top ; ) {
        int j = i;
        while(j + 1 <= top && a[p[j].x][p[j].y] == a[p[j + 1].x][p[j + 1].y]) ++ j;
        for(int k = i ; k <= j ; ++ k) {
            if((f[p[k].x] & f[p[k].y]).any()) {
                no;
            }
        }
        for(int k = i ; k <= j ; ++ k) {
            f[p[k].x][p[k].y] = 1;
        }
        i = j + 1;
    }

    yes;
}
