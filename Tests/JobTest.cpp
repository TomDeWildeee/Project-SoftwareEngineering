#include "gtest/gtest.h"
#include "../Job.h"

using namespace std;
class JobTest: public ::testing::Test{
protected:
    void SetUp() override{
    }
    void TearDown() override {
    }
};

TEST_F(JobTest, ConstructorTest) {
    auto* job = new ColorJob(100, 5, "Jan");
    EXPECT_NE(job->getJobNR(), 10);
    EXPECT_EQ(job->getJobNR(), 100);
    EXPECT_NE(job->getPageCount(), 10);
    EXPECT_EQ(job->getPageCount(), 5);
    EXPECT_NE(job->getUserName(), "Tom");
    EXPECT_EQ(job->getUserName(), "Jan");
    EXPECT_EQ(job->getJobType(), "color");
    delete job;
}