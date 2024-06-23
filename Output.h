#include <string>
#include <fstream>
#include <iostream>
#include "DesignByContract.h"

class OutputStream {
    OutputStream* _initCheck;
public:
    OutputStream();
    bool properlyInitialized();
    virtual void writeLine(const std::string& message) = 0;
    virtual ~OutputStream() = default;

    void writeErrorJobNrNotFound(int jobNR);
    void writeErrorNoDeviceOfCorrectType();
    void writePrintingPageNumber(int pageNR);
    void writeDeviceFinishedJob(const std::string &jobType, int jobNR, int jobPageCount,
                                const std::string &jobUsername, const std::string &processingDeviceName);

    void writeSystemDiagnosticTitle();
    void writeAdvancedPerDeviceOutput(const std::string &deviceType, const std::string &deviceName,
                             const std::string &jobQueueString, const std::string &finishedJobsString);

    void writeSystemReportHeader();

    void writeSystemReportDeviceInfo(const std::string &deviceType, const std::string &deviceName,
                                     const std::string &deviceSpeed, const std::string &deviceCost,
                                     const std::string &deviceEmission);
    void writeSystemReportJobInfo(const std::string &jobName, const std::string &jobUser, const std::string &jobPageCount,
                                  const std::string &jobDevice, const std::string &jobEmission, const std::string &jobCost);

    void writeSystemReportJobsHeader();
    void writeSystemReportNoPendingJobs();
    void writeSystemReportFooter();
};

class FileOutputStream : public OutputStream {
private:
    std::ofstream outputFile;
public:
    explicit FileOutputStream(const std::string& filename = "output.txt") : outputFile(filename) {}
/**
 REQUIRE(this->properlyInitialized(), "FileOutputStream wasn't initialized when writing line");
 */
    void writeLine(const std::string& message) override;
    ~FileOutputStream() override;
};

class ConsoleOutputStream : public OutputStream {
public:
/**
 REQUIRE(this->properlyInitialized(), "ConsoleOutputStream wasn't initialized when writing line");
 */
    void writeLine(const std::string& message) override;
};

class NoOutputStream : public OutputStream {
public:
/**
 REQUIRE(this->properlyInitialized(), "NoOutputStream wasn't initialized when writing line");
 */
    void writeLine(const std::string& message) override;
};