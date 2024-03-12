#include "DesignByContract.h"
#include "Job.h"

Job::Job(int jobNr, int pageCt, const std::string &userN) {
    jobNumber = jobNr;
    pageCount = pageCt;
    userName = userN;

    _initCheck = this;
    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

bool Job::properlyInitialized() {
    return _initCheck == this;
}

int Job::getJobNR() const {
    return jobNumber;
}

const std::string &Job::getUserName() const {
    return userName;
}
