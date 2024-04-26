#ifndef PROJECT_SOFTWAREENGINEERING_JOB_H
#define PROJECT_SOFTWAREENGINEERING_JOB_H

#include <string>

namespace JobType {
    enum JobTypeEnum {color, bw, scan};
}

class Job {
public:
    bool properlyInitialized();
/**
 Job will never be constructed with invalid parameters, because we check for that in the importer
 ENSURE(this->properlyInitialized(), "constructor must end in properlyInitialized state");
*/
    Job(int jobNr, int pageCt, const std::string &userN, JobType::JobTypeEnum jobType);

/**
 REQUIRE(this->properlyInitialized(), "Job wasn't initialized when getting jobnumber");
*/
    int getJobNR();

/**
 REQUIRE(this->properlyInitialized(), "Job wasn't initialized when getting username");
*/
    const std::string &getUserName();

/**
 REQUIRE(this->properlyInitialized(), "Job wasn't initialized when getting pagecount");
*/
    int getPageCount();

/**
 REQUIRE(this->properlyInitialized(), "Job wasn't initialized when getting job type");
*/
    std::string getJobType();

private:
    Job* _initCheck;

    int jobNumber;
    int pageCount;
    std::string userName;
    JobType::JobTypeEnum type;
};


#endif //PROJECT_SOFTWAREENGINEERING_JOB_H
