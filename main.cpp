#include "rational.h"
#include <bits/stdc++.h>

using namespace std;

int main(){
  Rational a(1);
  BigInteger b(1000000);
  b *= b;
  cout << double(a / b);
}
