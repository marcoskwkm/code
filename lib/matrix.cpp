template<class T> struct Matrix {
    vector< vector<T> > mat;
    int n, m;
    Matrix(int N, int M = -1) {
        if (M == -1) M = N;
        n = N, m = M;
        mat.resize(n);
        for (int i = 0; i < n; i++)
            mat[i] = vector<T>(m, 0);
    }
    vector<T>& operator[](int i) { return mat[i]; }
};

template<class T> Matrix<T> operator+ (Matrix<T> a, Matrix<T> b) {
    Matrix<T> m = a;
    for (int i = 0; i < m.n; i++)
        for (int j = 0; j < m.m; j++)
            m[i][j] += b[i][j];
    return m;
}

template<class T> Matrix<T> operator- (Matrix<T> a, Matrix<T> b) {
    Matrix<T> m = a;
    for (int i = 0; i < m.n; i++)
        for (int j = 0; j < m.m; j++)
            m[i][j] -= b[i][j];
    return m;
}

template<class T> Matrix<T> operator* (Matrix<T> a, Matrix<T> b) {
    Matrix<T> m(a.n, b.m);
    for (int i = 0; i < a.n; i++)
        for (int j = 0; j < b.m; j++)
            for (int k = 0; k < a.m; k++)
                m[i][j] += a[i][k] * b[k][j];
    return m;
}
    
template<class T> Matrix<T> operator* (T k, Matrix<T> a) {
    Matrix<T> m = a;
    for (int i = 0; i < m.n; i++)
        for (int j = 0; j < m.m; j++)
            m[i][j] *= k;
    return m;
}
