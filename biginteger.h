#ifndef __BigInteger
#define __BigInteger

#include <vector>
#include <iostream>
#include <string>

template<typename T>
void reverse(T &x) {
  for(size_t i = 0; i < x.size() / 2; ++i) {
    std::swap(x[i], x[x.size() - 1 - i]);
  }
}

class BigInteger{
public: 
  BigInteger();
  BigInteger(long long x);
  BigInteger(const std::string &s);
  BigInteger(const BigInteger &copy);

  ~BigInteger();

  std::string toString() const;

  friend BigInteger abs(const BigInteger &a);

  friend bool operator<(const BigInteger &a, const BigInteger &b);
  friend bool operator>(const BigInteger &a, const BigInteger &b);
  friend bool operator==(const BigInteger &a, const BigInteger &b);
  friend bool operator<=(const BigInteger &a, const BigInteger &b);
  friend bool operator>=(const BigInteger &a, const BigInteger &b);
  friend bool operator!=(const BigInteger &a, const BigInteger &b);

  explicit operator bool();

  BigInteger &operator+=(const BigInteger &b);
  BigInteger &operator-=(const BigInteger &b);
  BigInteger &operator*=(const BigInteger &b);
  BigInteger &operator/=(const BigInteger &b);
  BigInteger &operator%=(const BigInteger &b);
  BigInteger &operator=(const BigInteger &b);  
  BigInteger operator-() const;  
private:
  static const long long BASE = static_cast<long long>(1e5);
  static const size_t BASE_SIZE = 5;
  std::vector<long long> values;
  bool isPositive;
  
  void eraseLeadingZeros();
  void uniSum(const BigInteger &b, bool f);
  void sum(const BigInteger &b);
  void diff(const BigInteger &b);
  friend long long shortDiv(const BigInteger &a, const BigInteger &b);
  friend bool modLess(const BigInteger &a, const BigInteger &b);
};

BigInteger::BigInteger(){
  isPositive = true;
};

BigInteger::BigInteger(long long x) {
  if(x < 0) {
    isPositive = 0;
    x *= -1;
  } else {  
    isPositive = 1;
  }
  while(x) {
    values.push_back(x % BASE);
    x /= BASE;
  }
}

BigInteger::BigInteger(const std::string &s) {
  int sum = 0, pow = 1, c = 0;
  isPositive = 1;
  for(size_t i = s.size(); i > 0; --i) {
    if(s[i - 1] == '-') {
      isPositive = 0;
      break;
    }
    sum += (s[i - 1] - '0') * pow;
    pow *= 10;
    c++;

    if(c == BASE_SIZE) {
      values.push_back(sum);
      pow = 1;
      sum = 0;
      c = 0;
    }
  }

  values.push_back(sum);
  eraseLeadingZeros();
}

BigInteger::BigInteger(const BigInteger &copy) {
  if(&copy == this) {
    isPositive = 1;
    return; 
  }
  values = copy.values;
  isPositive = copy.isPositive;
}

std::string BigInteger::toString() const {
  std::string result;
  for(size_t i = 0; i < values.size(); ++i) {
    std::string tmp = std::to_string(values[i]);

    reverse(tmp);

    while(i + 1 != values.size() && tmp.size() < BASE_SIZE) {
      tmp.push_back('0');
    }
    result += tmp;
  }
  if(isPositive == 0) {
    result.push_back('-');
  }
  reverse(result);
  if(result.size() == 0) result = "0";
  return result;
}

BigInteger::~BigInteger(){};

BigInteger &BigInteger::operator=(const BigInteger &source)  {
  if(&source == this) 
    return *this;
  values = source.values;
  isPositive = source.isPositive;
  return *this;
}

void BigInteger::eraseLeadingZeros(){
  while(values.size() && values.back() == 0) values.pop_back();
  if(values.size() == 0) isPositive = 1;
}

bool modLess(const BigInteger &a, const BigInteger &b) {
  if(a.values.size() != b.values.size()) {
    return a.values.size() < b.values.size();
  }
  for(size_t i = a.values.size(); i > 0; --i) {
    if(a.values[i - 1] != b.values[i - 1]) {
      return a.values[i - 1] < b.values[i - 1];
    }
  } 
  return 0;
}

bool operator<(const BigInteger &a, const BigInteger &b) {
  if(a.isPositive != b.isPositive) {
    return b.isPositive;
  }
  if(a.isPositive) {
    return modLess(a, b);
  } else {
    return modLess(b, a);
  }
}

bool operator>(const BigInteger &a, const BigInteger &b) {
  return b < a;
}
 
bool operator!=(const BigInteger &a, const BigInteger &b) {
  return a < b || b < a;
}

bool operator==(const BigInteger &a, const BigInteger &b) {
  return !(a != b);
}

bool operator<=(const BigInteger &a, const BigInteger &b) {
  return !(a > b);
}

bool operator>=(const BigInteger &a, const BigInteger &b) {
  return !(a < b);
}

BigInteger BigInteger::operator-() const { 
  BigInteger result = *this;
  if(result.values.size()) {
    result.isPositive ^= 1;
  }
  return result;
}

void BigInteger::sum(const BigInteger &b) {
  values.resize(std::max(values.size(), b.values.size()) + 1, 0);  
  for(size_t i = 0; i < b.values.size(); ++i) {
    values[i] += b.values[i];
    if(values[i] >= BASE) {
      values[i + 1]++;
      values[i] -= BASE;
    }
  }
  for(size_t i = b.values.size(); i < values.size(); ++i) {
    if(values[i] >= BASE) {
      values[i + 1]++;
      values[i] -= BASE;
    }
  }

  eraseLeadingZeros();
}

void BigInteger::diff(const BigInteger &b) {
  values.resize(std::max(values.size(), b.values.size()) + 1, 0);
  for(size_t i = 0; i < b.values.size(); ++i) {
    values[i] -= b.values[i];
    if(values[i] < 0) {
      values[i + 1] -= 1;
      values[i] += BASE;
    }
  }
  for(size_t i = b.values.size(); i < values.size(); ++i) {
    if(values[i] < 0) {
      values[i + 1]--;
      values[i] += BASE;
    }
  }
  eraseLeadingZeros();
}

void BigInteger::uniSum(const BigInteger &b, bool f) {
  if(f) {
    sum(b);
  } else {
    if(modLess(*this, b)) {
      BigInteger s = *this;
      *this = b;
      diff(s);
      this->isPositive = s.isPositive ^ 1;
      eraseLeadingZeros();
    } else {
      diff(b);
    }
  }
}

BigInteger &BigInteger::operator+=(const BigInteger &b) {
  uniSum(b, isPositive == b.isPositive);
  return *this;
}

BigInteger &BigInteger::operator-=(const BigInteger &b) {
  uniSum(b, isPositive != b.isPositive);

  return *this;
}

BigInteger operator-(const BigInteger &a, const BigInteger &b) {
  BigInteger res = a;
  return res -= b;
}

BigInteger operator+(const BigInteger &a, const BigInteger &b) {
  BigInteger res = a;
  return res += b;
}

BigInteger::operator bool() {
  return this->values.size();
}

BigInteger &operator++(BigInteger &a) {
  return a += 1;
}

BigInteger &operator--(BigInteger &a) {
  return a -= 1;
}

BigInteger operator++(BigInteger &a, int) {
  BigInteger res = a;
  a += 1;
  return res;
}

BigInteger operator--(BigInteger &a, int) {
  BigInteger res = a;
  a -= 1;
  return res;
}

BigInteger &BigInteger::operator*=(const BigInteger &b) {
  BigInteger res;
  res.isPositive = this->isPositive == b.isPositive;
  res.values.resize(this->values.size() + b.values.size(), 0);
  for(size_t i = 0; i < this->values.size(); ++i) {
    for(size_t j = 0; j < b.values.size(); ++j) {
      res.values[i + j] += this->values[i] * b.values[j];
    }
  }
  *this = res;
  for(size_t i = 0; i < values.size(); ++i) {
    if(values[i] >= BASE) {
      if(i + 1 == values.size()) {
        values.push_back(0);
      }
      values[i + 1] += values[i] / BASE;
      values[i] %= BASE;
    }
  }
  eraseLeadingZeros();
  return *this;
}

BigInteger operator*(const BigInteger &a, const BigInteger &b) {
  BigInteger res = a;
  return res *= b;
}

BigInteger operator/(const BigInteger &a, const BigInteger &b) {
  BigInteger res = a;
  return res /= b;
}

long long shortDiv(const BigInteger &a, const BigInteger &b) {
  long long r = 2 * a.BASE, l = -1;
  while(r - l > 1) {
    long long mid = (r + l) / 2;
    if(b * mid <= a) {
      l = mid;
    } else {
      r = mid;
    }
  }
  return l;
}

BigInteger abs(const BigInteger &a) {
  BigInteger res = a;
  res.isPositive = 1;
  return res;
}

BigInteger &BigInteger::operator/=(const BigInteger &b) {
  BigInteger res;
  res.isPositive = this->isPositive == b.isPositive;
  
  BigInteger divider = abs(b);
  BigInteger divident = abs(*this);
  BigInteger buff;
  int it = static_cast<int>(divident.values.size());
  while(it > 0) {
    if(it > 0 && modLess(buff, divider)) {
      reverse(buff.values);
      buff.values.push_back(divident.values[--it]);
      reverse(buff.values);
    }
    buff.eraseLeadingZeros();
    if(!modLess(buff, divider)) {
      long long tmp = shortDiv(buff, divider);
      res.values.push_back(tmp);
      buff -= divider * tmp;
    } else {
      res.values.push_back(0);
    }
  }
  reverse(res.values);
  res.eraseLeadingZeros();
  // if(this->isPositive != b.isPositive && res * b != *this) {
  //   res -= 1;
  // }
  *this = res;  
  return *this;
}

BigInteger &BigInteger::operator%=(const BigInteger &b) {
  return *this -= *this / b * b;
}

BigInteger operator%(const BigInteger &a, const BigInteger &b) {
  BigInteger res = a;
  return res %= b;
}

std::istream &operator>>(std::istream &in, BigInteger &a) {
  std::string s;
  in >> s;
  a = BigInteger(s);
  return in;
}

std::ostream &operator<<(std::ostream &out, const BigInteger &a) {
  out << a.toString();
  return out;
}

BigInteger gcd(BigInteger a, BigInteger b) {
  while(b) {
    a %= b;
    std::swap(a, b);
  }
  return a;
}

#endif