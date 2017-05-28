template<class T> struct DynamicMedian {
    multiset<T> upper;
    multiset<T, greater<T>> lower;

    void insert(T x) {
        if (upper.empty() || x >= *upper.begin()) {
            upper.insert(x);
            if (upper.size() > lower.size() + 1) {
                lower.insert(*upper.begin());
                upper.erase(upper.begin());
            }
        }
        else {
            lower.insert(x);
            if (lower.size() > upper.size()) {
                upper.insert(*lower.begin());
                lower.erase(lower.begin());
            }
        }
    }

    void erase(T x) {
        if (upper.find(x) != upper.end()) {
            upper.erase(upper.find(x));
            if (lower.size() > upper.size()) {
                upper.insert(*lower.begin());
                lower.erase(lower.begin());
            }
        }
        else if (lower.find(x) != lower.end()) {
            lower.erase(lower.find(x));
            if (lower.size() + 1 < upper.size()) {
                lower.insert(*upper.begin());
                upper.erase(upper.begin());
            }
        }
    }

    T get_median() {
        return *upper.begin();
    }
};
