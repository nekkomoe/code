#include <bits/stdc++.h>
using namespace std;
 
char s[20];
int n;
int main() {
    scanf("%s", s + 1);
    int flag = 1;
    
    int n = strlen(s + 1), cnt = 0;
    flag = s[1] == 'A';
    // [3, n - 2]
    cnt = 0;
    for(int i = 3 ; i <= n - 1 ; ++ i) if(s[i] == 'C') ++ cnt;
    if(cnt != 1) flag = 0;
    
    cnt = 0;
    for(int i = 1 ; i <= n ; ++ i)
        if(!('a' <= s[i] && s[i] <= 'z')) {
            if(s[i] != 'A' && s[i] != 'C')
                        flag = 0;
        }
    
    
    if(flag) puts("AC");
    else puts("WA");
}
