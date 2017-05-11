#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, t, k, d, x;
    cin >> n >> t >> k >> d;
    if (n % k == 0) x = n/k*t; else x = (n/k+1)*t;
    if (x > t + d) cout << "YES"; else cout << "NO";
    return 0;
}
