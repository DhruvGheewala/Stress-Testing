#include <bits/stdc++.h>
#include "headers/generator.hpp"
using namespace std;

#define endl '\n'
#define int int64_t

void testcase(int tc) {
    int n = rnd(2, 20);
    vector<int> a;

    if(tc & 1) a = generateVector(n, -1000, 1000);
    else a = generateUniqueVector(n, -1000, 1000);

    cout << n << endl;
    for(int x: a)
        cout << x << ' ';
    cout << endl;
}

int32_t main(int32_t argc, char **argv) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T = rnd(1, 10);
    T = 2;
    cout << T << endl;
    for(int t = 1; t <= T; t++)
        testcase(t);
}
