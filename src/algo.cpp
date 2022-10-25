#include "maths/algo.hpp"

void algo::fft(std::vector<std::complex<double>>& a, bool invert) {
    size_t n =  a.size();
    if (n == 1)  return;

    std::vector<std::complex<double>> a0(n/2), a1(n/2);
    for (size_t i=0, j=0; i<n; i+=2, j++) {
        a0[j] = a[i];
        a1[j] = a[i+1];
    }
    fft (a0, invert);
    fft (a1, invert);

    double ang = 2*M_PI/n * (invert ? -1 : 1);
    std::complex<double> w(1),  wn(cos(ang), sin(ang));
    for (size_t i=0; i<n/2; ++i) {
        a[i] = a0[i] + w * a1[i];
        a[i+n/2] = a0[i] - w * a1[i];
        if (invert) a[i] /= 2,  a[i+n/2] /= 2;
        w *= wn;
    }
}
