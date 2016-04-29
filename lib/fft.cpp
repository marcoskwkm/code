typedef complex<long double> Complex;
const long double PI = acos(-1.0L);

// Computes the DFT of vector v if type = 1, or the IDFT if type = -1
// If you are calculating the product of polynomials, don't forget to set both
// vectors' degrees to at least the sum of degrees of both polynomials, regardless
// of whether you will use only the first few elements of the resulting array
vector<Complex> FFT(vector<Complex> v, int type) {
    int n = v.size();
    while(n&(n-1)) { v.push_back(0); n++; }
    int logn = __builtin_ctz(n);
    vector<Complex> v2(n);
    for(int i=0; i<n; i++) {
        int mask = 0;
        for(int j=0; j<logn; j++) if(i&(1<<j)) mask |= (1<<(logn - 1 - j));
        v2[mask] = v[i];
    }
    for(int s=0, m=2; s<logn; s++, m<<=1) {
        Complex wm(cos(2.L * type * PI / m), sin(2.L * type * PI / m));        
        for(int k=0; k<n; k+=m) {
            Complex w = 1;
            for(int j=0; 2*j<m; j++) {
                Complex t = w * v2[k + j + (m>>1)], u = v2[k + j];
                v2[k + j] = u + t; v2[k + j + (m>>1)] = u - t;
                w *= wm;
            }
        }
    }
    if(type == -1) for(Complex &c: v2) c /= n;
    return v2;
}
