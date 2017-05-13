template<class T> void assert_equal_vectors(vector<T> a, vector<T> b) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    assert(a == b);
}
