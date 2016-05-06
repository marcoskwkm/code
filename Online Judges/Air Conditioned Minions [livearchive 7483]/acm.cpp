#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

struct Event {
    int t;
    int kind, i;
    Event(int a, int b, int c) {
        t = a; kind = b; i = c;
    }
};

bool foi[MAXN];

int main() {
    int n;
    while (scanf("%d", &n) > 0) {
        memset(foi, 0, sizeof(foi));
        vector<Event> events;
        for (int i = 0; i < n; i++) {
            int l, r;
            scanf("%d%d", &l, &r);
            events.push_back(Event(l, 0, i));
            events.push_back(Event(r, 1, i));
        }
        sort(events.begin(), events.end(), [](Event a, Event b) {
            if (a.t == b.t) return a.kind < b.kind;
            return a.t < b.t;
        });
        int ans = 0;
        stack<int> st;
        for (Event event: events) {
            if (foi[event.i]) continue;
            if (event.kind == 0) {
                st.push(event.i);
            }
            else {
                ans++;
                while (!st.empty()) {
                    foi[st.top()] = 1;
                    st.pop();
                }
            }
        }
        printf("%d\n", ans);
    }        
    return 0;
}
