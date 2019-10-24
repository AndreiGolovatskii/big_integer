#include <bits/stdc++.h>
#include "biginteger.h"

int checkSum(const std::string &a, const std::string &b, const std::string &res) {
  BigInteger ba(a), bb(b);
  BigInteger bres;
  bres = ba + bb;

  return bres.toString() == res;
}
int checkMul(const std::string &a, const std::string &b, const std::string &res) {
  BigInteger ba(a), bb(b);
  BigInteger bres;
  bres = ba * bb;

  return bres.toString() == res;
}
int checkDiv(const std::string &a, const std::string &b, const std::string &res) {
  BigInteger ba(a), bb(b);
  BigInteger bres;
  bres = ba / bb;

  return bres.toString() == res;
}
int checkMod(const std::string &a, const std::string &b, const std::string &res) {
  BigInteger ba(a), bb(b);
  BigInteger bres;
  bres = ba % bb;

  return bres.toString() == res;
}
int checkInc(const std::string &a, const std::string &res) {
  BigInteger aa(a);
  assert(a == (aa++).toString());
  return aa.toString() == res;
}
int checkDec(const std::string &a, const std::string &res) {
  BigInteger aa(a);
  assert(a == (aa--).toString());

  return aa.toString() == res;
}
int checkDiff(const std::string &a, const std::string &b, const std::string &res) {
  BigInteger ba(a), bb(b);
  BigInteger bres;
  bres = ba - bb;

  return bres.toString() == res;
}
int checkCopy(const std::string &a, const std::string &b) {
  BigInteger first, second(a);
  first = second;
  return(first.toString() == b);
}

int checkInit(const std::string &a, const std::string &b) {
  BigInteger second(a);
  BigInteger first = second;

  return(first.toString() == b);
}
int checkLess(const std::string &a, const std::string &b, int res) {
  BigInteger ia(a), ib(b);
  return (ia < ib) == res;
}
int checkNotLess(const std::string &a, const std::string &b, int res) {
  BigInteger ia(a), ib(b);
  return (ia >= ib) == res;
}
int checkGreat(const std::string &a, const std::string &b, int res) {
  BigInteger ia(a), ib(b);
  return (ia > ib) == res;
} 
int checkNotGreat(const std::string &a, const std::string &b, int res) {
  BigInteger ia(a), ib(b);
  return (ia <= ib) == res;
}
int checkEqual(const std::string &a, const std::string &b, int res) {
  BigInteger ia(a), ib(b);
  return (ia == ib) == res;
}

void testEngene() {
  if(!freopen("test.txt", "r", stdin)){
    return;
  }

  int testCount;
  std::cin >> testCount;
  std::cout << "Start Test:\n";
  for(int i = 0; i < testCount; ++i) {
    std::string testType;
    std::cin >> testType;
    if(testType == "sum") {
      std::string a, b, res;
      std::cin >> a >> b >> res;
      if(!checkSum(a, b, res)) {
        std::cout << "Sum error\n";
        exit(0);
      }
    } else if(testType == "diff") {
      std::string a, b, res;
      std::cin >> a >> b >> res;
      if(!checkDiff(a, b, res)) {
        std::cout << "Diff error\n";
        std::cout << testType << " " << a << " " << b << " " << res << '\n';
        exit(0);
      }

    } else if(testType == "init"){
      std::string a, b;
      std::cin >> a >> b;
      if(!checkInit(a, b)) {
        std::cout << "Init error\n";
        exit(0);
      }
    } else if(testType == "copy") {
      std::string a, b;
      std::cin >> a >> b;
      if(!checkCopy(a, b)) {
        std::cout << "Copy error\n";
        exit(0);
      }
    } else if(testType == "less") {
      std::string a, b;
      int result;
      std::cin >> a >> b >> result;
      if(!checkLess(a, b, result)) {
        std::cout << "Less error\n";
        exit(0);
      }
    } else if(testType == "notless"){
      std::string a, b;
      int result;
      std::cin >> a >> b >> result;
      if(!checkNotLess(a, b, result)) {
        std::cout << "NotLess error\n";
        exit(0);
      }  
    } else if(testType == "great"){
      std::string a, b;
      int result;
      std::cin >> a >> b >> result;
      if(!checkGreat(a, b, result)) {
        std::cout << "Great error\n";
        exit(0);
      }  
    } else if(testType == "notgreat"){
      std::string a, b;
      int result;
      std::cin >> a >> b >> result;
      if(!checkNotGreat(a, b, result)) {
        std::cout << "NotGreat error\n";
        exit(0);
      }  
    } else if(testType == "equal") {
      std::string a, b;
      int result;
      std::cin >> a >> b >> result;
      if(!checkEqual(a, b, result)) {
        std::cout << "Equal error\n";
        exit(0);
      }
    } else if(testType == "inc"){
      std::string a, b;
      std::cin >> a >> b;
      if(!checkInc(a, b)) {
        std::cout << "Inc error\n";
        exit(0);
      }
    } else if(testType == "dec"){
      std::string a, b;
      std::cin >> a >> b;
      if(!checkDec(a, b)) {
        std::cout << "dec error\n";
        exit(0);
      } 
    } else if(testType == "mul") {
      std::string a, b, c;
      std::cin >> a >> b >> c;
      if(!checkMul(a, b, c)) {
        std::cout << "Mul error\n";
        exit(0);
      }
    } else if(testType == "div") {
      std::string a, b, c;
      std::cin >> a >> b >> c;
      if(!checkDiv(a, b, c)) {
        std::cout << "Div error\n";
        exit(0);
      }
    } else if(testType == "mod") {
      std::string a, b, c;
      std::cin >> a >> b >> c;
      if(!checkMod(a, b, c)) {
        std::cout << "Mod error\n";
        exit(0);
      }
    } else {
      assert(0);
    }
    std::cout << i + 1 << ": Ok:\n";
  }
  std::cout << "All tests passed\n";
}


int main() {
  auto ts = std::clock();
  testEngene(); 
  std::cout << "time: " << ((double)std::clock() - ts) / CLOCKS_PER_SEC;
}
