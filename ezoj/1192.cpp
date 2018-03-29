%:pragma GCC optimize(2)
%:pragma GCC optimize(3)

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <ext/rope>

using namespace std;
using namespace __gnu_cxx;

int l, r, n;

char str[250010];

int main() {
    scanf("%s", str);
    rope<char> s(str);
    while(scanf("%s", str) == 1) {
        if(str[0] == 'E') break;
        else if(str[0] == 'I') {
            scanf("%s%d", str, &l);
            for(int i = 0 ; str[i] ; ++ i) {
                s.insert(i + l, str[i]);
            }
        } else if(str[0] == 'P') {
            scanf("%d%d", &l, &r);
            printf("%s\n", s.substr(l, r - l + 1).c_str());
        }
    }
}
