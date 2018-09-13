#include <bits/stdc++.h>
using namespace std;
const int N = 20000000 + 10;
int n, a[N], cnt[5];
char s[N], t[N];
 
void A() {
    puts("clccle trl!");
    exit(0);
}
 
void B() {
    puts("sarlendy tql!");
    exit(0);
}
 
void C() {
    puts("orz sarlendy!");
    exit(0);
}
 
int main() {
    scanf("%d%s%s", &n, s, t);
    for(int i = 0 ; i < 2 * n ; ++ i) {
        if(s[i] == 'U' && t[i] == 'U') {
            ++ cnt[1];
        } else if(s[i] == 'U' && t[i] == 'D') {
            ++ cnt[2];
        } else if(s[i] == 'D' && t[i] == 'U') {
            ++ cnt[3];
        } else {
            ++ cnt[4];
        }
    }
    if(cnt[1] & 1) ++ cnt[2];
    if(cnt[2] != cnt[3]) {
        if(cnt[2] < cnt[3]) {
            B();
        } else {
            A();
        }
    } else {
        C();
    }
}
