// test_classes.cpp

#include "classes.h"
#include <gtest/gtest.h>

TEST(COneTest, DefaultConstructor) {
    COne obj;
    EXPECT_EQ(obj.toString(), "COne: n = 0, s = ");
}

TEST(CTwoTest, ParameterConstructor) {
    COne one(10, "Example");
    CTwo two(3.14, &one);
    EXPECT_EQ(two.getD(), 3.14);
    EXPECT_NE(two.getP(), nullptr);
}

TEST(CThreeTest, AdditionalField) {
    COne one(5, "Data");
    CThree three(2.71, &one, 42);
    EXPECT_EQ(three.getAdditionalField(), 42);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

