#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <complex>

using namespace std;

typedef complex<double> c;

const double eps = 1e-4;

c A, B, C, p[3];

void input(c &p) {
    double x, y;
    scanf("%lf%lf", &x, &y);
    p = c(x, y);
}

void output(c x) {
    printf("%.6lf %.6lf\n", x.real(), x.imag());
}

int equ(c a, c b) {
    return fabs(a.real() - b.real()) < eps && (a.imag() - b.imag()) < eps;
}

int check(c _A, c _B, c _C) {
    c T = (_A - _B) / (A - B), P = (A * T - _A) / (T - c(1));
    if(equ((C - P) * T, _C - P)) {
        output(P);
        return 1;
    }
    return 0;
}

void sol() {
    input(A), input(B), input(C);
    input(p[0]), input(p[1]), input(p[2]);
    int cho[3] = { 0, 1, 2 };
    do if(check(p[cho[0]], p[cho[1]], p[cho[2]])) return ;
    while(next_permutation(cho, cho + 3));
}

int main() {
    int T; scanf("%d", &T); while(T --) sol();
}

