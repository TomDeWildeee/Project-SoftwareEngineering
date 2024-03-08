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