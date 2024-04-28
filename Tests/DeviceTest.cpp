#include "gtest/gtest.h"
#include "../Device.h"

using namespace std;
class DeviceTest: public ::testing::Test{
protected:
    void SetUp() override{
    }
    void TearDown() override {
    }
};

TEST_F(DeviceTest, ConstructorTest) {
    auto* device = new Device("Printer1", 20, 5, DeviceType::DeviceTypeEnum::color, 5);
    EXPECT_NE(device->getName(), "Printer8");
    EXPECT_EQ(device->getName(), "Printer1");
    EXPECT_NE(device->getEmissions(), 10);
    EXPECT_EQ(device->getEmissions(), 20);
    EXPECT_NE(device->getSpeed(), 10);
    EXPECT_EQ(device->getSpeed(), 5);
    delete device;
}