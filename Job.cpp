#include "DesignByContract.h"
#include "Job.h"

//Job will never be constructed with invalid parameters, because we check for that in the importer
Job::Job(int jobNr, int pageCt, const std::string &userN, JobType::JobTypeEnum jobType) {
    jobNumber = jobNr;
    pageCount = pageCt;
    userName = userN;
    type = jobType;

    _initCheck = this;
    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

bool Job::properlyInitialized() {
    return _initCheck == this;
}

int Job::getJobNR() {
    REQUIRE(this->properlyInitialized(), "Job wasn't initialized when getting jobnumber");
    return jobNumber;
}

const std::string &Job::getUserName() {
    REQUIRE(this->properlyInitialized(), "Job wasn't initialized when getting username");
    return userName;
}

int Job::getPageCount() {
    REQUIRE(this->properlyInitialized(), "Job wasn't initialized when getting pagecount");
    return pageCount;
}

std::string Job::getJobType() {
    REQUIRE(this->properlyInitialized(), "Job wasn't initialized when getting job type");
    if (type == JobType::color) {
        return "color";
    } else if (type == JobType::bw) {
        return "bw";
    } else {
        return "scan";
    }
}

/*
Device *Job::getDevice() {
    REQUIRE(this->properlyInitialized(), "Job wasn't initialized when getting processing device");
    return device;
}

void Job::setDevice(Device* processingDevice) {
    REQUIRE(this->properlyInitialized(), "Job wasn't initialized when setting processing device");
    Job::device = processingDevice;
}
*/
