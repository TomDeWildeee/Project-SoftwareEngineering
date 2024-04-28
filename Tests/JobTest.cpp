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
    auto* job = new Job(100, 5, "Jan", JobType::JobTypeEnum::color);
    EXPECT_NE(job->getJobNR(), 10);
    EXPECT_EQ(job->getJobNR(), 100);
    EXPECT_NE(job->getPageCount(), 10);
    EXPECT_EQ(job->getPageCount(), 5);
    EXPECT_NE(job->getUserName(), "Tom");
    EXPECT_EQ(job->getUserName(), "Jan");
    delete job;
}