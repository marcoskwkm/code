#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr,x)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

class TheKingsFactorization {
public:
    vector<long long> getVector(long long N, vector<long long> primes);
};

vector<long long> TheKingsFactorization::getVector(long long N, vector<long long> primes) {
    if(primes.size() == 0) return vector<lint>(1,N);
    for(lint p: primes) N /= p;
    vector<lint> factors = primes;
    for(lint d = 2; d <= 2000000 || d*d*d <= N; ++d) {
        if(N % d == 0) {
            do {
                N /= d;
                factors.push_back(d);
            } while(N % d == 0);
        }
    }
    if(N > 1) {
        lint l = 2, r = 1e18+10;
        while(l<r) {
            lint mid = (l+r)/2;
            if(mid*mid <= N) r = mid;
            else l = mid+1;
        }
        if(l*l == N) {
            factors.push_back(l);
            factors.push_back(l);
        }
        else factors.push_back(N);
    }
    sort(factors.begin(),factors.end());
    return factors;
}

// BEGIN CUT HERE
namespace moj_harness {
    int run_test_case(int);
    void run_test(int casenum = -1, bool quiet = false) {
        if (casenum != -1) {
            if (run_test_case(casenum) == -1 && !quiet) {
                cerr << "Illegal input! Test case " << casenum << " does not exist." << endl;
            }
            return;
        }
		
        int correct = 0, total = 0;
        for (int i=0;; ++i) {
            int x = run_test_case(i);
            if (x == -1) {
                if (i >= 100) break;
                continue;
            }
            correct += x;
            ++total;
        }
		
        if (total == 0) {
            cerr << "No test cases run." << endl;
        } else if (correct < total) {
            cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << endl;
        } else {
            cerr << "All " << total << " tests passed!" << endl;
        }
    }
	
    template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << "{"; for (typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " " << *vi; } os << " }"; return os; }

    int verify_case(int casenum, const vector<long long> &expected, const vector<long long> &received, clock_t elapsed) { 
        cerr << "Example " << casenum << "... "; 
		
        string verdict;
        vector<string> info;
        char buf[100];
		
        if (elapsed > CLOCKS_PER_SEC / 200) {
            sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
            info.push_back(buf);
        }
		
        if (expected == received) {
            verdict = "PASSED";
        } else {
            verdict = "FAILED";
        }
		
        cerr << verdict;
        if (!info.empty()) {
            cerr << " (";
            for (int i=0; i<(int)info.size(); ++i) {
                if (i > 0) cerr << ", ";
                cerr << info[i];
            }
            cerr << ")";
        }
        cerr << endl;
		
        if (verdict == "FAILED") {
            cerr << "    Expected: " << expected << endl; 
            cerr << "    Received: " << received << endl; 
        }
		
        return verdict == "PASSED";
    }

    int run_test_case(int casenum__) {
        switch (casenum__) {
        case 0: {
            long long N               = 12;
            long long primes[]        = {2, 3};
            long long expected__[]    = {2, 2, 3};

            clock_t start__           = clock();
            vector<long long> received__ = TheKingsFactorization().getVector(N, vector<long long>(primes, primes + (sizeof primes / sizeof primes[0])));
            return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }
        case 1: {
            long long N               = 7;
            long long primes[]        = {7};
            long long expected__[]    = {7};

            clock_t start__           = clock();
            vector<long long> received__ = TheKingsFactorization().getVector(N, vector<long long>(primes, primes + (sizeof primes / sizeof primes[0])));
            return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }
        case 2: {
            long long N               = 1764;
            long long primes[]        = {2, 3, 7};
            long long expected__[]    = {2, 2, 3, 3, 7, 7};

            clock_t start__           = clock();
            vector<long long> received__ = TheKingsFactorization().getVector(N, vector<long long>(primes, primes + (sizeof primes / sizeof primes[0])));
            return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }
        case 3: {
            long long N               = 49;
            long long primes[]        = {7};
            long long expected__[]    = {7, 7};

            clock_t start__           = clock();
            vector<long long> received__ = TheKingsFactorization().getVector(N, vector<long long>(primes, primes + (sizeof primes / sizeof primes[0])));
            return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }
        case 4: {
            long long N               = 210;
            long long primes[]        = {2, 5};
            long long expected__[]    = {2, 3, 5, 7};

            clock_t start__           = clock();
            vector<long long> received__ = TheKingsFactorization().getVector(N, vector<long long>(primes, primes + (sizeof primes / sizeof primes[0])));
            return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }
        case 5: {
            long long N               = 100000;
            long long primes[]        = {2, 2, 2, 5, 5};
            long long expected__[]    = {2, 2, 2, 2, 2, 5, 5, 5, 5, 5};

            clock_t start__           = clock();
            vector<long long> received__ = TheKingsFactorization().getVector(N, vector<long long>(primes, primes + (sizeof primes / sizeof primes[0])));
            return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }

            // custom cases

/*      case 6: {
        long long N               = ;
        long long primes[]        = ;
        long long expected__[]    = ;

        clock_t start__           = clock();
        vector<long long> received__ = TheKingsFactorization().getVector(N, vector<long long>(primes, primes + (sizeof primes / sizeof primes[0])));
        return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }*/
/*      case 7: {
        long long N               = ;
        long long primes[]        = ;
        long long expected__[]    = ;

        clock_t start__           = clock();
        vector<long long> received__ = TheKingsFactorization().getVector(N, vector<long long>(primes, primes + (sizeof primes / sizeof primes[0])));
        return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }*/
/*      case 8: {
        long long N               = ;
        long long primes[]        = ;
        long long expected__[]    = ;

        clock_t start__           = clock();
        vector<long long> received__ = TheKingsFactorization().getVector(N, vector<long long>(primes, primes + (sizeof primes / sizeof primes[0])));
        return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
        }*/
        default:
            return -1;
        }
    }
}
 

int main(int argc, char *argv[]) {
    if (argc == 1) {
        moj_harness::run_test();
    } else {
        for (int i=1; i<argc; ++i)
            moj_harness::run_test(atoi(argv[i]));
    }
}
// END CUT HERE
