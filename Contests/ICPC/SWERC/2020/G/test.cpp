#include <bits/stdc++.h>
using namespace std;

int main() {
    for (int line = 0; line < nlines; line++) {
        string s;
        getline(cin, s);
        stringstream ss(line);
        string op;
        int idx;
        while (ss >> op >> idx) {
            printf("%s %d\n", op.c_str(), idx);
        }
    }
}
