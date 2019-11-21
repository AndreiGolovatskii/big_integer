#ifndef FAST_FOURIER_TRANSFORM
#define FAST_FOURIER_TANSSFORM

#include <complex>
#include <vector>
#include <assert.h>
#include <algorithm>

std::vector<int> revBit(int log_n) {
  int n = 1 << log_n;

  std::vector<int> rev(n, 0);
  for(int i = 0; i < n; ++i) {
    rev[i] =(rev[i >> 1] >> 1) + ((i & 1) << (log_n - 1));
  } 
  return rev;
}


std::vector<std::complex<double>> roots(int log_n) {
  int n = 1 << log_n;

  std::vector<std::complex<double>> root(n, 0);
  for(int k = 1; k < n; k *= 2) {
    std::complex<double> tmp(std::cos(M_PI / k), std::sin(M_PI / k));
  
    root[k] = {1, 0};
    for(int i = 1; i < k; ++i) {
      root[k + i] = root[(k + i) >> 1];
      if((i & 1)) root[k + i] *= tmp;
    }
  }
  return root;
}

std::vector<std::complex<double>> fft(const std::vector<std::complex<double>> &in, const std::vector<int> &rev, const std::vector<std::complex<double>> &root) {
  int n = static_cast<int>(in.size());
  std::vector<std::complex<double>> result(n);

  for(int i = 0; i < n; ++i) {
    result[rev[i]] = in[i];
  }

  for(int k = 1; k < n; k *= 2) {
    for(int i = 0; i < n; i += 2 * k) {
      for(int j = 0; j < k; ++j) {
        std::complex<double> tmp = root[k + j] * result[i + j + k];
        result[i + j + k] = result[i + j] - tmp;
        result[i + j] = result[i + j] + tmp;
      }
    }
  }
  return result;
}


std::vector<std::complex<double>> fft_inverse(const std::vector<std::complex<double>> &in, const std::vector<int> &rev, const std::vector<std::complex<double>> &root) {
  std::vector<std::complex<double>> result = fft(in, rev, root);
  std::reverse(result.begin() + 1, result.end());
  for(size_t i = 0; i < result.size(); ++i) {
    result[i] /= static_cast<int>(result.size());
  }
  return result;
}

std::vector<std::complex<double>> toComplex(const std::vector<long  long> &a, int log_n) {
  std::vector<std::complex<double>> result(1 << log_n, 0);
  for(size_t i = 0; i < a.size(); ++i) {
    result[i] = static_cast<std::complex<double>>(a[i]);
  }
  return result;
}

std::vector<long long> toLongLong(const std::vector<std::complex<double>> &a) {
  std::vector<long long> result(a.size(), 0);
  for(size_t i = 0; i < a.size(); ++i) {
    result[i] = static_cast<long long>(round(a[i].real()));
  }
  return result;
}

std::vector<long long> multiply_polynomials(const std::vector<long long> &a, const std::vector<long long> &b) {
  int log_n = 0;
  while((1 << log_n) < 2 * static_cast<int>(std::max(a.size(), b.size()))) {
    ++log_n;
  }

  std::vector<std::complex<double>> ca = toComplex(a, log_n);
  std::vector<std::complex<double>> cb = toComplex(b, log_n);

  std::vector<int> rev = revBit(log_n);
  std::vector<std::complex<double>> root = roots(log_n);

  std::vector<std::complex<double>> ra = fft(ca, rev, root);
  std::vector<std::complex<double>> rb = fft(cb, rev, root);

  for(size_t i = 0; i < ra.size(); ++i) {
    ra[i] *= rb[i];
  }

  std::vector<std::complex<double>> result = fft_inverse(ra, rev, root);

  return toLongLong(result);
}


#endif