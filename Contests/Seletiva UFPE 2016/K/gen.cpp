#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(0));
    int n = 10000;
    printf("%d\n", n);
    vector<int> v;
    for (int i = 1; i <= n; i++)
        v.push_back(i);
    reverse(v.begin(), v.end());
    for (int x: v) printf("%d ", x);
    printf("\n");
    return 0;
}
