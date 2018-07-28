#include "bits/stdc++.h"
using namespace std;
int n;
int main() {
    scanf("%d", &n);
    if(n == 1) {
        puts("1");
        puts("1");
    } else if(n == 2) {
        puts("1");
        puts("1");
    } else if(n == 3) {
        puts("2");
        puts("1 3");
    } else if(n == 4) {
        puts("4");
        puts("3 1 4 2");
    } else {
        printf("%d\n", n);
        for(int i = 1 ; i <= n ; i += 2) printf("%d ", i);
        for(int i = 2 ; i <= n ; i += 2) printf("%d ", i);
        puts("");
    }
}
