#include "polynomial.h"

#include <vector>

#include <gtest/gtest.h>

using std::vector;
using FF::Polynomial;


// Tests factorial of negative numbers.
TEST(PolynomialTest, Addition) {
  EXPECT_EQ(4, 2 + 2);
}

TEST(PolynomialTest, Equality) {
  vector<int> v1;
  v1.push_back(3);
  v1.push_back(5);
  Polynomial<int> p1(v1);

  vector<int> v2;
  v2.push_back(3);
  v2.push_back(7);
  Polynomial<int> p2(v2);

  EXPECT_EQ(p1 == p1, true);
  EXPECT_EQ(p2 == p2, true);
  EXPECT_EQ(p1 == p2, false);

  vector<int> v3(v2);
  v3.push_back(0);
  Polynomial<int> p3(v3);
  EXPECT_EQ(p3 == p2, true);
  EXPECT_EQ(p3 == p1, false);
}
