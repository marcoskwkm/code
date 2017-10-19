/*
  Fast Walsh-Hadamard Transform - O(N*logN)
  Similar to FFT, but instead of sum, computes OR, AND or XOR.
*/

enum FWHT_OP { OR, AND, XOR };
const vector<vector<int>> T = {{1, 1, 1, 0},  {0, 1, 1, 1},  {1, 1, 1, -1}};
const vector<vector<int>> I = {{0, 1, 1, -1}, {-1, 1, 1, 0}, {1, 1, 1, -1}};
vector<lint> FWHT(vector<lint> v, int type, FWHT_OP op) {
    while (v.size() & (v.size() - 1)) v.push_back(0);
    for (size_t len = 1; 2 * len <= v.size(); len *= 2) {
        for (size_t i = 0; i < v.size(); i += 2 * len) {
            for (size_t j = 0; j < len; j++) {
                lint x = v[i + j], y = v[i + len + j];
                if (type == 1) {
                    v[i + j] = T[op][0] * x + T[op][1] * y;
                    v[i + len + j] = T[op][2] * x + T[op][3] * y;
                }
                else {
                    v[i + j] = I[op][0] * x + I[op][1] * y;
                    v[i + len + j] = I[op][2] * x + I[op][3] * y;
                }
            }
        }
    }
    if (op == XOR && type == -1)
        for (auto &x: v)
            x /= v.size();
    return v;
}    
