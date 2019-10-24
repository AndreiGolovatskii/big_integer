
// #include <bits/stdc++.h>
#include <iostream>
// #include "biginteger.h"
#include "rational.h"

using namespace std;
void testEngine() {
  Rational r;
  int b = 15;
  r = 5;
  r += 3;
  r *= 7; // r==56
  (r /= 8) -= b; //r = 7-15=-8
  if (-r != 8) {
    cout << "BAD\n";
  }
        
  Rational s = Rational(85)/37, t = Rational(29)/BigInteger(-163);
    
  s += t;
    
  t = 1;
  t *= s;
  if ((1/t).toString() != "507972178875842800075597772950831264898404875587494819951")
  {
    cout << "BAD\n";
  }
  s = 4*3*7*13*19*41*43*11; // 2^2×3×7×13×19×41×43×11
  t = -17*13*23*79;
  s *= s*s, t *= t*t;
  Rational q = s/t;
  if (q.toString() != "-29650611427828166204352/29472131485369")
  {
    cout << "BAD\n";
  }
  if (q/1000000000 >= 1)
  {
    cout << "BAD\n";

  }
  if (0/q != 0)
  {
    cout << "BAD\n";

  }
  q *= t/s;

  if (q != 1 || q.toString() != "1")
  {
    cout << "BAD\n";
  }

  if (q != 1 || q.toString() != "1")
  {
    cout << "BAD\n";
  }
  s = 4*3*7*13*19*41*43*11;
  t = s - 25; // t=402365939
  ((s = 1000000007) *= 1000000009) *= 2147483647;
  if ((s/t).asDecimal(10) != "5337140829307966068.3989202202")
  {
    cout << "BAD\n";

  }
  t = -t;
  if ((t/s).asDecimal(25) != "-0.0000000000000000001873662")
  {
    cout << "BAD\n";

  }
}

int main(){
  testEngine();
}
