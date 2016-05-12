#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    string s, V, C;
    string vowels = "aeiouy";
    cin >> s;
    for (char c: s) {
        bool isvowel = 0;
        for (char vowel: vowels)
            if (c == vowel)
                isvowel = 1;
        if (isvowel) V += c;
        else C += c;
    }
    printf("%s\n", V > C ? "Vowel" : "Consonant");
    return 0;
}
