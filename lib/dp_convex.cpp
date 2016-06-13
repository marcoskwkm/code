// Convex Hull Optimization (general case)
// O(logn) for insertion and query
// Test: SPOJ GOODG

template< class C_TYPE, class Compare = less<C_TYPE> > struct ConvexHullOpt {
    struct Line {
        C_TYPE a, b; // a + bx
        double end_l, end_r;
        Line(){}
        Line(C_TYPE aa, C_TYPE bb) { a = aa; b = bb; end_l = -1e80, end_r = 1e80; }
        inline C_TYPE get(C_TYPE x) const { return a + b*x; }
    };

    struct by_slope {
        bool operator()(const Line &a, const Line &b) const {
            return Compare()(a.b, b.b);
        }
    };
        
    struct by_end {
        bool operator()(const Line &a, const Line &b) const {
            return a.end_r < b.end_r;
        }
    };

    inline double cross(const Line &a, const Line &b) {
        return double(b.a - a.a) / (a.b - b.b);
    }

    set<Line, by_slope> set_slope;
    set<Line, by_end> set_end;

    void add_line(C_TYPE a, C_TYPE b) {
        Line newline(a, b);
        auto itr = set_slope.lower_bound(newline);
        auto itr2 = itr == set_slope.end() ? set_end.end() : set_end.lower_bound(*itr);
        if (itr != set_slope.end()) {
            if (cross(*itr, newline) < itr->end_l) return;
            while (itr != set_slope.end() && cross(*itr, newline) > itr->end_r) {
                itr = set_slope.erase(itr);
                itr2 = set_end.erase(itr2);
            }
            if (itr != set_slope.end()) {
                double x = cross(*itr, newline);
                Line tmp = *itr;
                newline.end_r = tmp.end_l = x;
                itr = set_slope.erase(itr);
                itr = set_slope.insert(itr, tmp);
                itr2 = set_end.erase(itr2);
                itr2 = set_end.insert(itr2, tmp);
            }
        }
        auto itl = itr;
        auto itl2 = itr2;
        while (itl != set_slope.begin()) {
            itl--, itl2--;
            double x = cross(*itl, newline);
            if (x > itl->end_l) {
                Line tmp = *itl;
                newline.end_l = tmp.end_r = x;
                itl = set_slope.erase(itl);
                itl = set_slope.insert(itl, tmp);
                itl2 = set_end.erase(itl2);
                itl2 = set_end.insert(itl2, tmp);
                break;
            }
            itl = set_slope.erase(itl);
            itl2 = set_end.erase(itl2);
        }
        set_slope.insert(itr, newline);
        set_end.insert(itr2, newline);
    }

    C_TYPE get(C_TYPE x) {
        if (set_end.empty()) return -LINF;
        Line dummy;
        dummy.end_r = x;
        auto it = set_end.lower_bound(dummy);
        return it->get(x);
    }
};
