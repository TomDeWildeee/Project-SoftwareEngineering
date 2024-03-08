#include <gtest/gtest.h>
#include <algorithm>
#include "PrintingSystem.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


class LargestTest: public ::testing::Test {
protected:

    void SetUp() override {

    }

    void TearDown() override {

    }
};

TEST_F(LargestTest, SimpleTest) {
    std::vector<int> some_numbers = std::vector<int>();
    some_numbers.push_back(3);
    some_numbers.push_back(5);
    some_numbers.push_back(-11);

    auto it = std::max_element(some_numbers.begin(), some_numbers.end());

    EXPECT_EQ(5, *it);
}