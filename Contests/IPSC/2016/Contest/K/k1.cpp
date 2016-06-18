#include <bits/stdc++.h>
using namespace std;

long long median(long long a, long long b, long long c) {
    if (a > b) swap(a,b);
    if (a > c) swap(a,c);
    if (b > c) swap(b,c);
    return b;
}

long long f1(long long n) {
    return (-n*n*n + 947*n*n + 20647474747LL*n + 47) / 20000000047LL;
}

long long f2(long long n) {
    return (-n*n + 2084747*n + 47) / 2494747;
}

long long f3(long long n) {
    return (-n*n*n + 19647*n*n + 23254474747LL*n - 25384747*(n%97)*n + 47 ) / 25382294747LL;
}

const int MAXN = 10010;
int l[MAXN];

void sort_helper(vector<unsigned> &A, int lo, int hi) {
    if (l[lo] >= hi) return;
    bool sorted = 1;
    for (int i = lo; i + 1 < hi; i++) {
        if (A[i] > A[i + 1]) {
            sorted = 0;
            break;
        }
    }
    if (sorted) {
        l[lo] = hi;
        return;
    }
    // fprintf(stderr, "%d %d\n", lo, hi);
    long long n = hi - lo;
    if (n <= 2) {
        if (n == 2 && A[lo] > A[lo+1]) swap( A[lo], A[lo+1] );
        // fprintf(stderr, "ret %d %d\n", lo, hi);
        return;
    }
    long long a = median( 0, n-1, f1(n) );
    long long b = median( 0, n-1, f2(n) );
    long long c = median( 0, n-1, f3(n) );
    sort_helper( A, lo, lo+a );
    sort_helper( A, hi-b, hi );
    sort_helper( A, lo, lo+c );
    // fprintf(stderr, "ret %d %d\n", lo, hi);
}

// this is the main function
void k1_sort(vector<unsigned> &A) {
    sort_helper( A, 0, A.size() );
}

int main(int argc, char* argv[]) {
    // vector<unsigned> v;
    // int n;
    // sscanf(argv[1], "%d", &n);
    // for (int i = n; i >= 1; i--)
    //     v.push_back(i);
    // k1_sort(v);
    // for (auto x: v) cout << x << endl;
    // return 0;
    for (int nn = 3; nn <= 1000000; nn++) {
        long long a = median( 0, nn-1, f1(nn) );
        long long b = median( 0, nn-1, f2(nn) );
        long long c = median( 0, nn-1, f3(nn) );
        int l1 = 0, r1 = a - 1;
        int l2 = nn - b, r2 = nn - 1;
        int l3 = 0, r3 = c - 1;
        printf("%d: (%d, %d), (%d, %d), (%d, %d)\n", nn, l1, r1, l2, r2, l3, r3);
        bool ok = 1;
        if (r1 - l2 + 1 < l2 - l1) ok = 0;
        if (r3 - l2 + 1 < r2 - r3) ok = 0;
        if (!ok) {
            printf("%d\n", nn);
            // for (int i = nn; i >= 1; i--) printf("%d ", i);
            // printf("\n");
            break;
        }
    }
    
    // printf("%s\n", ok ? "OK" : "FAIL");
    return 0;
}
