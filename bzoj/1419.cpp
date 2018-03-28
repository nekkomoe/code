//期望dp
 
%:pragma GCC optimize(2)
%:pragma GCC optimize(3)
 
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
 
using namespace std;
 
const int N = 5010;
 
int r, b, p;
 
double f[2][N];
 
int main() {
    scanf("%d%d", &r, &b);
    for(register int i = 0 ; i <= r ; ++ i) {
        p ^= 1;
        for(register int j = 0 ; j <= b ; ++ j) {
            if(i == 0) f[p][j] = 0;
            else if(j == 0) f[p][j] = i;
            else f[p][j] = max(0.0,
                (i * 1.0 / (i + j) * (f[p ^ 1][j] + 1)) + 
                (j * 1.0 / (i + j) * (f[p][j - 1] - 1)));
        }
    }
    printf("%.6lf", (double)int(f[p][b] * 1e6) / 1e6);
}