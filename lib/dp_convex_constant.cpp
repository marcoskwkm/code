// Convex Hull Optimization (constant query variant)
// Requires:
//   1. Lines are inserted in strict order of slope:
//      increasing -> max, decreasing -> min
//   2. Queries are made in increasing order of x.

template<class C_TYPE> struct ConvexHullOpt {
    struct Line {
        C_TYPE a, b; // a + bx
        double end_l;
        C_TYPE get(C_TYPE x) { return a + b*x; }
        Line(){}
        Line(C_TYPE aa, C_TYPE bb) { a = aa; b = bb; end_l = -LINF; }
    };

    vector<Line> deq;
    int deq_l;

    C_TYPE cross(const Line &r, const Line &s) {
        return double(s.a - r.a) / (r.b - s.b);
    }

    ConvexHullOpt() { clear(); }

    void add_line(C_TYPE a, C_TYPE b) {
        Line newline(a, b);
        while (deq_l < (int)deq.size() &&
               cross(newline, deq.back()) < deq.back().end_l)
            deq.pop_back();
        if (deq_l < (int)deq.size()) newline.end_l = cross(newline, deq.back());
        deq.push_back(newline);
    }

    C_TYPE get(C_TYPE x) {
        if (deq_l >= (int)deq.size()) {
            // can't query with no lines in structure =P
            abort();
        }
        while (deq_l + 1 < (int)deq.size() && deq[deq_l + 1].end_l <= x)
            deq_l++;
        return deq[deq_l].get(x);
    }

    void clear() {
        deq.clear();
        deq_l = 0;
    }
};
