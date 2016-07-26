#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

tm* get_tm(int year, int month, int day, int hour = 0, int min = 0, int sec = 0) {
    tm *date = new tm();
    date->tm_year = year - 1900;
    date->tm_mon = month - 1;
    date->tm_mday = day;
    date->tm_hour = hour;
    date->tm_min = min;
    date->tm_sec = sec;
    mktime(date);
    return date;
}

// Returns the Unix timestamp for the given date interpreted as local time
int get_timestamp(int year, int month, int day, int hour = 0, int min = 0, int sec = 0) {
    tm *date = get_tm(year, month, day, hour, min, sec);
    return mktime(date);
}

const int MAXN = 5010;

struct Event {
    int t, k;
    Event(int tt, int kk) { t = tt, k = kk; }
};

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int n, clean_time;
        scanf("%d%d", &n, &clean_time);
        clean_time *= 60;
        vector<Event> events;
        for (int i = 0; i < n; i++) {
            string foo;
            int year, month, day, hr, min;            
            scanf("%*s%d%*c%d%*c%d%d%*c%d", &year, &month, &day, &hr, &min);
            events.push_back(Event(get_timestamp(year, month, day, hr, min), 1));
            scanf("%d%*c%d%*c%d%d%*c%d", &year, &month, &day, &hr, &min);
            events.push_back(Event(get_timestamp(year, month, day, hr, min) + clean_time, 0));
        }
        sort(events.begin(), events.end(), [](Event a, Event b) {
            if (a.t == b.t) return a.k < b.k;
            return a.t < b.t;
        });
        int ans = 0, cur = 0;
        for (const Event &event: events) {
            if (event.k == 1) cur++;
            else cur--;
            ans = max(ans, cur);
        }
        printf("%d\n", ans);
    }        
    return 0;
}
