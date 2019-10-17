#ifndef __BIGINTEGER
#define __BIGINTEGER

#include <vector>
#include <assert.h>
#include <string>

class bigInteger{
  public: 
    bigInteger(){};
    bigInteger(long long x);
    bigInteger(char *s);
    std::string toString();
  private:
    static const long long BASE = static_cast<long long>(1e5);
    std::vector<long long> values;
    bool sign;
    
    void normalize();

    bigInteger moduloSum(const bigInteger &b) const;
    bigInteger moduloDifference(const bigInteger&b) const;

    bool operator<(const bigInteger &b) const;
    bool moduloLess(const bigInteger &b) const;

    bigInteger operator+(const bigInteger &b) const;
    bigInteger operator-(const bigInteger &b) const;
    bigInteger operator-() const;

    
};

void bigInteger::normalize() {
  for(size_t i = 0; i < values.size(); ++i) {
    if(values[i] > BASE) {
      if(i + 1 == values.size()) {
        values.push_back(0);
      }
      values[i + 1] += values[i] / BASE;
      values[i] %= BASE;
    }
  }

  while(values.back() == 0) values.pop_back();
}

bigInteger bigInteger::moduloSum(const bigInteger &b) const {
  bigInteger result;
  
  size_t n = std::max(values.size(), b.values.size());
  result.values.resize(n, 0);
  for(size_t i = 0; i < n; ++i) {
    result.values[i] = (i < values.size() ? values[i] : 0) + (i < b.values.size() ? b.values[i] : 0);
  }

  result.normalize();
  return result;
}

bigInteger bigInteger::moduloDifference(const bigInteger &b) const {
  bigInteger result;
  
  size_t n = std::max(values.size(), b.values.size());
  result.values.resize(n, 0);
  for(size_t i = 0; i < n; ++i) {
    result.values[i] = (i < values.size() ? values[i] : 0) - (i < b.values.size() ? b.values[i] : 0);
  }

  result.normalize();
  return result;
}
bool bigInteger::moduloLess(const bigInteger &b) const {
  if(values.size() != b.values.size()) {
    return values.size() < b.values.size();
  }
  for(size_t i = values.size(); i > 0; --i) {
    if(values[i - 1] != b.values[i - 1]) {
      return values[i - 1] < b.values[i - 1];
    }
  }
  
  return 0;
}
bool bigInteger::operator<(const bigInteger &b) const {
  if(sign != b.sign) {
    return sign < b.sign;
  }
  return moduloLess(b) ^ sign;
}

bigInteger bigInteger::operator-() const { 
  bigInteger result = *this;
  result.sign ^= 1;
  return result;
}

bigInteger bigInteger::operator-(const bigInteger &b) const {
  bigInteger result;
  if(sign == 1 && b.sign == 1) {
    if(moduloLess(b)) {
      result = b.moduloDifference(*this);
      result.sign = sign ^ 1;
    } else {
      result = moduloDifference(b);
      result.sign = sign;
    }
  } else if(sign == 1 && b.sign == -1) {
    result = moduloSum(b);
    result.sign = sign;
  } else if(sign == -1 && b.sign == 1) {
    result = moduloSum(b);
    result.sign = sign;
  } else {
    if(moduloLess(b)) {
        result.sign = sign ^ 1;
    }
  }
  return result;
}

bigInteger bigInteger::operator+(const bigInteger &b) const {
  bigInteger result;
  if(sign == b.sign) {
    result.sign = sign;
    result = moduloSum(b);
  } else {
    if(moduloLess(b)) {
      result.sign = sign ^ 1;
      result = b.moduloDifference(*this);
    } else {
      result.sign = sign;
      result = moduloDifference(b);
    }
  }
  return result;
}



#endif