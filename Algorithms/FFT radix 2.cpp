#include<complex>
namespace FFT {
  typedef std::complex<double> comp;
  const double PI = acos(-1);
  int getpow(int x) {
    int r = 0;
    while ((1 << r) < x) r++;
    return r;
  }
  // 2^p >= degree
  void fft(comp *ar, int p, int mode) {  // 1 for normal, -1 for inverse
    int L = 1 << p;
    for (int i=0, x=0, j=0; i < L; i++, x=i, j=0) {
      for (int k = 0; k < p; k++, x>>=1) j=j<<1|x&1;
      if (j > i) swap(ar[i], ar[j]);
    }
    for (int i = 1; i <= p; i++) {
      int l = (1 << i);
      comp base(cos(2*PI/l), mode * sin(2*PI/l));
      comp cur(1, 0);
      for (int j = 0; j < l/2; j++) {
        for (int k = 0; k < L; k += l) {
          comp A = ar[k + j];
          comp B = cur * ar[k + j+l/2];
          ar[k + j] = A + B;
          ar[k + j+l/2] = A - B;
        }
        cur *= base;
      }
    }
    if (mode == -1)
      for (int i = 0; i < L; i++)
        ar[i].real((ar[i].real() + 0.5) / L);
  }
  void convolve(comp *ar, comp *br, int p) {
    for (p = 1 << p; p >= 0; p--)
      ar[p] = ar[p] * br[p];
  }
}