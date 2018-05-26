//( cmp(a,b) _ 0 ) means (a _ b)
inline int cmp(double a, double b = 0) {
    return (a < b + EPS) ? (a + EPS < b) ? -1 : 0 : 1;
}
