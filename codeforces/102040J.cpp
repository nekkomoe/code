#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        double price;scanf("%lf", &price);
        double output = price * 1.15;
        printf("%.2lf\n", output);       
    }
}
