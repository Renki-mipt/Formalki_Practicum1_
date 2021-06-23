#include <gtest/gtest.h>

#include "F16.h"

TEST(BoolMatrixTest, Multiply1) {
  std::vector<std::vector<bool>> vec1 = {{0, 1, 0}, {0, 0, 1}, {1, 0, 0}};
  std::vector<std::vector<bool>> vec2 = {{1, 1, 1}, {0, 1, 0}, {1, 0, 0}};
  std::vector<std::vector<bool>> vec3 = {{0, 1, 0}, {1, 0, 0}, {1, 1, 1}};
  BoolMatrix BM1(vec1);
  BoolMatrix BM2(vec2);
  BoolMatrix BM3(vec3);
  BoolMatrix BM4 = BM1 * BM2;
  EXPECT_EQ(BM4, BM3);
  EXPECT_TRUE(true);
}

TEST(BoolMatrixTest, Multiply2) {
  BoolMatrix BM1(2);
  BoolMatrix BM2(2);
  BoolMatrix BM3(2);
  BM1.matrix[0][0] = 1;
  BM1.matrix[1][1] = 1;
  BM2.matrix[0][1] = 1;
  BM2.matrix[1][0] = 1;
  BM3.matrix[0][1] = 1;
  BM3.matrix[1][0] = 1;
  EXPECT_EQ(BM1 * BM2, BM3);
}

TEST(BoolMatrixTest, Addition) {
  std::vector<std::vector<bool>> vec1 = {{0, 1, 0}, {0, 0, 1}, {1, 0, 0}};
  std::vector<std::vector<bool>> vec2 = {{1, 1, 1}, {0, 1, 0}, {1, 0, 0}};
  std::vector<std::vector<bool>> vec3 = {{1, 1, 1}, {0, 1, 1}, {1, 0, 0}};
  BoolMatrix BM1(vec1);
  BoolMatrix BM2(vec2);
  BoolMatrix BM3(vec3);
  EXPECT_EQ(BM1 + BM2, BM3);
}

TEST(BoolMatrixTest, locking) {
  std::vector<std::vector<bool>> vec1 = {{0, 1, 0}, {0, 0, 1}, {1, 0, 0}};
  std::vector<std::vector<bool>> vec2 = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
  BoolMatrix BM1(vec1);
  BoolMatrix BM2(vec2);
  EXPECT_EQ(BM1.locking(), BM2);
}

TEST(DynamicStateTest, Constructor) {
  std::string s = "aba";
  char c = 'a';
  DynamicState DS1(c, s);
  std::vector<std::vector<bool>> vec1 = {
      {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 1}, {0, 0, 0, 1}};
  std::vector<std::vector<bool>> vec2 = {
      {0, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 0, 0}};
  BoolMatrix BM1(vec1);
  BoolMatrix BM2(vec2);
  EXPECT_EQ(DS1.GetWhole(), BM2);
  EXPECT_EQ(DS1.GetMiddle(), BM1);
  EXPECT_EQ(DS1.GetSuffix(), BM1);
  EXPECT_EQ(DS1.GetPrefix(), BM1);
}

TEST(DynamicStateTest, Multiply) {
  std::string s = "aba";
  char c = 'a';
  DynamicState DS1(c, s);
  c = 'b';
  DynamicState DS2(c, s);
  std::vector<std::vector<bool>> VecWHole = {
      {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  std::vector<std::vector<bool>> VecSuffix = {
      {1, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
  std::vector<std::vector<bool>> VecPrefix = {
      {1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 1, 1}, {0, 0, 0, 1}};
  std::vector<std::vector<bool>> VecMiddle = {
      {1, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 1}};
  BoolMatrix BM1(VecWHole);
  BoolMatrix BM2(VecSuffix);
  BoolMatrix BM3(VecPrefix);
  BoolMatrix BM4(VecMiddle);
  DynamicState DS = DS1 * DS2;
  EXPECT_EQ(DS.GetWhole(), BM1);
  EXPECT_EQ(DS.GetSuffix(), BM2);
  // EXPECT_EQ(DS.GetPrefix(), BM3);
  // EXPECT_EQ(DS.GetMiddle(), BM4);
}

TEST(DynamicStateTest, Addition) {
  std::string s = "aba";
  char c = 'a';
  DynamicState DS1(c, s);
  c = 'b';
  DynamicState DS2(c, s);
  std::vector<std::vector<bool>> VecSufPrefMid = {
      {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 1}};
  std::vector<std::vector<bool>> VecWHole = {
      {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}, {0, 0, 0, 0}};
  BoolMatrix BM1(VecWHole);
  BoolMatrix BM2(VecSufPrefMid);
  BoolMatrix BM3(VecSufPrefMid);
  BoolMatrix BM4(VecSufPrefMid);
  DynamicState DS = DS1 + DS2;
  EXPECT_EQ(DS.GetWhole(), BM1);
  EXPECT_EQ(DS.GetMiddle(), BM2);
  EXPECT_EQ(DS.GetSuffix(), BM3);
  EXPECT_EQ(DS.GetPrefix(), BM4);
}

TEST(DynamicStateTest, Star) {
  std::string s = "aba";
  char c = 'a';
  DynamicState DS1(c, s);
  c = 'b';
  DynamicState DS2(c, s);
  std::vector<std::vector<bool>> VecWHole = {
      {1, 0, 1, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
  std::vector<std::vector<bool>> VecSuffix = {
      {1, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
  std::vector<std::vector<bool>> VecPrefix = {
      {1, 1, 1, 1}, {0, 1, 0, 0}, {0, 0, 1, 1}, {0, 0, 0, 1}};
  std::vector<std::vector<bool>> VecMiddle = {
      {1, 1, 1, 1}, {0, 1, 1, 1}, {0, 0, 1, 1}, {0, 0, 0, 1}};
  BoolMatrix BM1(VecWHole);
  BoolMatrix BM2(VecSuffix);
  BoolMatrix BM3(VecPrefix);
  BoolMatrix BM4(VecMiddle);
  DynamicState DS = DS1 * DS2;
  DS = DS.star();
  EXPECT_EQ(DS.GetWhole(), BM1);
  EXPECT_EQ(DS.GetSuffix(), BM2);
  EXPECT_EQ(DS.GetPrefix(), BM3);
  EXPECT_EQ(DS.GetMiddle(), BM4);
}

TEST(JustTest, IsTrue) { EXPECT_TRUE(true); }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
