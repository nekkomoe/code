#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
 
const int N = 100010;
 
int lst[30], nxt[N][30], n;
 
char s[N];
 
int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for(int i = n ; i ; -- i) {
        int c = s[i] - 'a';
        for(int j = 0 ; j < 26 ; ++ j) nxt[i][j] = lst[j];
        lst[c] = i;
    }
    for(int i = 25 ; ~ i ; -- i) {
        if(lst[i]) {
            int c = i;
            int p = lst[c];
            do {
                putchar('a' + c);
                int f = 0;
                for(int j = 25 ; ~ j ; -- j) {
                    if(nxt[p][j]) {
                        f = 1;
                        c = j, p = nxt[p][j];
                        break;
                    }
                }
                if(!f) return 0;
            } while(1);
        }
    }
}
