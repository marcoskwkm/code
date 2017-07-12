#include <bits/stdc++.h>
using namespace std;

int t;
string s;
int rem[10];
int ans[30];

int main() {
    scanf(" %d", &t);
    while (t--) {
        cin >> s;
        vector<int> sa;
        bool f = false;
        for (char c : s) {
            if (c == '0' && !f); 
            else {
                f = true;
                sa.push_back(c -'0');
            }
        }
        int n = sa.size();
        if (n > 20) {
            cout << "99887766554433221100" << endl;
            continue;
        }
        int comp = 999999999;
        for (int i = 0; i < 10; i++)
            rem[i] = 2;
        memset(ans, 0, sizeof(ans));
        bool jump = false;
        for (int i = 0; i < n && !jump; i++) {
            int x = sa[i];
            //printf("debug x = %d rem[x] = %d\n", x, rem[x]);
            if (rem[x] > 0) {
                ans[i] = x;
                rem[x]--;
            }
            else {
                for (int j = x-1; j >= 0 && !jump; j--) {
                    if (rem[j] > 0) {
                        //printf("debug j = %d rem[j] = %d\n", j, rem[j]);
                        ans[i] = j;
                        rem[j]--;
                        jump = true;
                        comp = i+1;
                    }
                }
                for (int j = i-1; j >= 0 && !jump; j--) {
                    int cur = sa[j];
                    rem[cur]++;
                    if (cur > 0) {
                        for (int k = cur-1; k >= 0 && !jump; k--) {
                            if (rem[k] > 0) {
                                ans[j] = k;
                                rem[k]--;
                                jump = true;
                                comp = j+1;
                            }
                        }
                    }
                }
            }
        }
        for (int i = comp; i < n; i++) {
            for (int j = 9; j >= 0; j--) {
                if (rem[j] > 0) {
                    ans[i] = j;
                    rem[j]--;
                    break;
                }
            }
        }
        bool flag = false;
        for (int i = 0; i < n; i++) {
            if (ans[i] == 0 && !flag) continue;
            printf("%d", ans[i]);
            flag = true;
        }
        printf("\n");
    }
    return 0;
}

