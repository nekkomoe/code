// 数论 gcd 数学 阶乘

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

int a, b;

long long fac(int a) {
    return a == 0 ? 1 : fac(a - 1) * a;
}

int main() {
    cin >> a >> b;
    if(a > b) swap(a, b);
    cout << fac(a);
}
