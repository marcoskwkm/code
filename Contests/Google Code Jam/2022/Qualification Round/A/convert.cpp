#include <bits/stdc++.h>
using namespace std;

int main() {
    map<char, string> mp;
    mp[' '] = "";
    mp['#'] = "38";
    mp['('] = "a58";
    mp[')'] = "b58";
    mp['*'] = "b48";
    mp['+'] = "a68";
    mp[','] = "038";
    mp['-'] = "b";
    mp['.'] = "a38";
    mp['1'] = "1";
    mp[':'] = "28";
    mp['='] = "68";
    mp['C'] = "a3";
    mp['T'] = "03";
    mp['['] = "a28";
    mp['\''] = "58";
    mp['\\'] = "028";
    mp['\n'] = "059";
    mp[']'] = "b28";
    mp['a'] = "a01";
    mp['e'] = "a05";
    mp['f'] = "a06";
    mp['g'] = "a07";
    mp['i'] = "a09";
    mp['j'] = "ab1";
    mp['l'] = "ab3";
    mp['m'] = "ab4";
    mp['n'] = "ab5";
    mp['o'] = "ab6";
    mp['p'] = "ab7";
    mp['r'] = "ab9";
    mp['s'] = "b02";
    mp['t'] = "b03";
    mp['u'] = "b04";
    mp['{'] = "a0";
    mp['|'] = "ab";
    mp['}'] = "b0";

    char c;
    while (scanf("%c", &c) != EOF) {
        printf("%s: %s\n", c == '\n' ? "\\n" : string(1, c).c_str(), mp[c].c_str());
    }
    return 0;
}
