#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

string vowel = "aiyeou";
string cons = "bkxznhdcwgpvjqtsrlmf";

int main() {
    string line;
    while (getline(cin, line)) {
        for (char &c: line) {
            bool upper = isupper(c);
            for (int i = 0; i < (int)vowel.size(); i++) {
                if (tolower(c) == vowel[i]) {
                    c = vowel[(i + 3)%6];
                    break;
                }
            }
            for (int i = 0; i < (int)cons.size(); i++) {
                if (tolower(c) == cons[i]) {
                    c = cons[(i + 10)%cons.size()];
                    break;
                }
            }
            if (upper) c = toupper(c);
        }
        printf("%s\n", line.c_str());
    }
    return 0;
}
