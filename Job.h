#ifndef PROJECT_SOFTWAREENGINEERING_JOB_H
#define PROJECT_SOFTWAREENGINEERING_JOB_H


#include <string>

class Job {
private:
    Job* _initCheck;
    int jobNumber;
    int pageCount;
    std::string userName;
public:
    Job(int jobNr, int pageCt, const std::string &userN);
    bool properlyInitialized();

    int getJobNR() const;
    const std::string &getUserName() const;

    int getPageCount() const;
};


#endif //PROJECT_SOFTWAREENGINEERING_JOB_H
