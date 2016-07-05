// Uses Simpson's rule to integrate f from x0 to x1 using 2*n subintervals
double integrate(function<double(double)> f, double x0, double x1, int n) {
    n *= 2; // n must be even
    double h = (x1 - x0) / n;
    double sum = f(x0) + f(x1);
    for (int i = 1; 2*i <= n; i++) {
        if (2*i < n) sum += 2*f(x0 + 2*i*h);
        sum += 4*f(x0 + (2*i - 1)*h);
    }
    return sum * h / 3;
}    
