#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 15;

vector<char> hand[MAXN];
int joker[MAXN];
int n, k;

bool isWinner(int idx) {
    if (joker[idx]) return 0;
    for (int i = 1; i < 4; i++)
        if (hand[idx][i] != hand[idx][0])
            return 0;
    return 1;
}

int pickCard(int idx) {
    map<char, int> freq;
    for (char card: hand[idx])
        freq[card]++;

    const string cards = "A23456789DQJK";
    char pickedCard;
    int pickedFreq = INF;
    for (char card: cards) {
        if (0 < freq[card] && freq[card] < pickedFreq) {
            pickedFreq = freq[card];
            pickedCard = card;
        }
    }

    // debug("player %d picked card: %c\n", idx, pickedCard);

    for (int i = 0; i < (int) hand[idx].size(); i++)
        if (hand[idx][i] == pickedCard)
            return i;

    return -1;
}

void play(int idx) {
    const int nextIdx = (idx + 1) % n;
    if (joker[idx] == 2) {
        joker[nextIdx] = 1;
        joker[idx] = 0;
    } else {
        int cardIdx = pickCard(idx);
        swap(hand[idx][cardIdx], hand[idx].back());
        hand[nextIdx].push_back(hand[idx].back());
        hand[idx].pop_back();

        if (joker[idx] == 1) {
            joker[idx] = 2;
        }
    }
}

int main() {
    cin >> n >> k;

    joker[k - 1] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            char c;
            scanf(" %c", &c);
            hand[i].push_back(c);
        }
        if (isWinner(i)) {
            printf("%d\n", i + 1);
            return 0;
        }
    }

    for (k--;; k = (k + 1) % n) {
        // for (int i = 0; i < n; i++) {
        //     for (char c: hand[i])
        //         debug("%c", c);
        //     debug(" (%d)\n", joker[i]);
        // }
        // debug("\n");
        
        play(k);
        if (isWinner(k)) {
            printf("%d\n", k + 1);
            break;
        }
    }
    
    return 0;
}
