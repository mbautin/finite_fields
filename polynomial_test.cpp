#include "polynomial.h"

#include <gtest/gtest.h>

using std::vector;
using std::cout;
using std::endl;
using FF::Polynomial;

TEST(PolynomialTest, Equality) {
  vector<int> v1;
  v1.push_back(3);
  v1.push_back(5);
  Polynomial<int> p1(v1);

  vector<int> v2;
  v2.push_back(3);
  v2.push_back(7);
  Polynomial<int> p2(v2);

  EXPECT_TRUE(p1 == p1);
  EXPECT_TRUE(p2 == p2);
  EXPECT_FALSE(p1 == p2);

  vector<int> v3(v2);
  v3.push_back(0);
  Polynomial<int> p3(v3);
  EXPECT_TRUE(p3 == p2);
  EXPECT_FALSE(p3 == p1);
}


TEST(PolynomialTest, StringConversion) {
  EXPECT_EQ("2*x^4 - 5*x^3 + 3*x^2 + 1", Polynomial<int>({1, 0, 3, -5, 2}).str());
  EXPECT_EQ("-2", Polynomial<int>({-2}).str());
  EXPECT_EQ("0", Polynomial<int>().str());
  EXPECT_EQ("0", Polynomial<int>({}).str());
  EXPECT_EQ("0", Polynomial<int>({0}).str());
  EXPECT_EQ("0", Polynomial<int>({0, 0}).str());
  EXPECT_EQ("-10*x", Polynomial<int>({0, -10}).str());
  EXPECT_EQ("-7*x^3", Polynomial<int>({0, 0, 0, -7}).str());
  EXPECT_EQ("-x^2", Polynomial<int>({0, 0, -1}).str());
}

TEST(PolynomialTest, Addition) {
  auto p1 = Polynomial<int>({0, -5, 2});
  auto p2 = Polynomial<int>({-2, 5, 3});
  EXPECT_EQ("5*x^2 - 2", (p1 + p2).str());
}

TEST(PolynomialTest, PolynomialByPolynomialMultiplication) {
  EXPECT_EQ("2*x^2 - 6*x", (Polynomial<int>({-3, 1}) * Polynomial<int>({0, 2})).str());
}
