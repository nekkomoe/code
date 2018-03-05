#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int a, b;

int main() {
    while(scanf("%d%d", &a, &b) == 2) {
        if(a > b) swap(a, b);
        puts((int) ((b - a) * (sqrt(5.0) + 1) / 2) == a ? "0" : "1");
    }
}