#include "prime_field.h"

#include <gtest/gtest.h>

using std::vector;
using std::cout;
using std::endl;


static auto z5_zero = PrimeField<int, 5>(0);
static auto z5_one = PrimeField<int, 5>(1);
static auto z5_two = PrimeField<int, 5>(2);
static auto z5_three = PrimeField<int, 5>(3);
static auto z5_four = PrimeField<int, 5>(4);


TEST(PrimeField, Addition) {

  EXPECT_EQ(z5_three, z5_zero + z5_three);
  EXPECT_EQ(z5_three, z5_one + z5_two);
  EXPECT_EQ(z5_one, z5_three + z5_three);
  EXPECT_EQ(z5_one, z5_four + z5_two);

  EXPECT_NE(z5_one, z5_two + z5_two);

  auto negative_eight(PrimeField<int, 5>(-8));
  EXPECT_EQ(z5_zero, z5_three + negative_eight);
}

TEST(PrimeField, Multiplication) {
  EXPECT_EQ(z5_one, z5_one * z5_one);
  EXPECT_EQ(z5_four, z5_two * z5_two);
  EXPECT_EQ(z5_one, z5_two * z5_three);
}

TEST(PrimeField, Division) {
  EXPECT_EQ(z5_two, z5_one / z5_three);
  EXPECT_EQ(z5_three, z5_one / z5_two);
  EXPECT_EQ(z5_four, z5_one / z5_four);
  EXPECT_EQ(z5_four, z5_two / z5_three);
  EXPECT_EQ(z5_two, z5_three / z5_four);
}
