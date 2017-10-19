struct Polynomial {
    vector<lint> coef;
    
    Polynomial(const vector<lint> &c) : coef(c) { reduce(); }

    void reduce() {
        while (coef.size() > 1 && coef.back() == 0)
            coef.pop_back();
    }
    
    Polynomial operator-(const Polynomial &q) {
        Polynomial p(coef);
        while (p.coef.size() < q.coef.size()) p.coef.push_back(0);
        for (size_t i = 0; i < q.coef.size(); i++)
            p.coef[i] -= q.coef[i];
        p.reduce();
        return p;
    }
    
    Polynomial operator*(const Polynomial &q) {
        vector<lint> prod(coef.size() + q.coef.size());
        for (size_t i = 0; i < coef.size(); i++)
            for (size_t j = 0; j < q.coef.size(); j++)
                prod[i + j] += coef[i] * q.coef[j];
        return Polynomial(prod);
    }

    Polynomial derivative() {
        vector<lint> vd(coef.size() - 1);
        for (int i = 0; i < (int)coef.size() - 1; i++)
            vd[i] = coef[i + 1] * (i + 1);
        return Polynomial(vd);
    }

    string to_string() {
        string ret = ::to_string(coef.back()) + "x^" + ::to_string(coef.size() - 1);
        for (int i = (int)coef.size() - 2; i >= 0; i--)
            ret += " + " + ::to_string(coef[i]) + "x^" + ::to_string(i);
        return ret;
    }        
};
