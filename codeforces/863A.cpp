//模拟 判断回文串

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <vector>

using namespace std;

int x;

vector<int> v;

int main() {
    scanf("%d", &x);
    while(x % 10 == 0 && x) x /= 10;
    do {
        v.push_back(x % 10);
        x /= 10;
    } while(x);
    for(int i = 0 ; i < v.size() / 2 ; i ++) {
        if(v[i] != v[v.size() - 1 - i]) {
            puts("NO");
            return 0;
        }
    }
    puts("YES");
}
