#include "prime_field.h"

#include <gtest/gtest.h>

using std::vector;
using std::cout;
using std::endl;

TEST(PrimeField, Addition) {
  auto a(PrimeField<int, 5>(3));
  auto b(PrimeField<int, 5>(-8));
  cout << (a + b).get_value() << endl;
//  EXPECT_EQ(PrimeField<int, 5>(0), a + b);
}


