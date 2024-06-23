#include "Output.h"

OutputStream::OutputStream() {
    _initCheck = this;
    ENSURE(this->properlyInitialized(), "OutputStream wasn't properly initialized");
}

bool OutputStream::properlyInitialized() {
    return _initCheck;
}

void FileOutputStream::writeLine(const std::string &message) {
    REQUIRE(this->properlyInitialized(), "FileOutputStream wasn't initialized when writing line");
    outputFile << message << std::endl;
}

FileOutputStream::~FileOutputStream() {
    outputFile.close();
}

void ConsoleOutputStream::writeLine(const std::string &message) {
    REQUIRE(this->properlyInitialized(), "ConsoleOutputStream wasn't initialized when writing line");
    std::cout << message << std::endl;
}

void NoOutputStream::writeLine(const std::string &message) {
    REQUIRE(this->properlyInitialized(), "NoOutputStream wasn't initialized when writing line");

}

// Generating right strings and writing them

void OutputStream::writeErrorJobNrNotFound(int jobNR) {
    REQUIRE(this->properlyInitialized(), "OutputStream wasn't initialized when writing this string");
    writeLine("ERR: JOB with job number: \" + std::to_string(jobNR) + \" can not be found");
}

void OutputStream::writeErrorNoDeviceOfCorrectType() {
    REQUIRE(this->properlyInitialized(), "OutputStream wasn't initialized when writing this string");
    writeLine("ERR: There is no device of the correct type to process job");
}

void OutputStream::writePrintingPageNumber(int pageNR) {
    REQUIRE(this->properlyInitialized(), "OutputStream wasn't initialized when writing this string");
    writeLine("Printing page " + std::to_string(pageNR));
}

void OutputStream::writeDeviceFinishedJob(const std::string &jobType, int jobNR, int jobPageCount,
                                          const std::string &jobUsername, const std::string &processingDeviceName) {
    std::string typestring;
    if(jobType == "color") {
        typestring = "color-printing";
    } else if(jobType == "bw") {
        typestring = "black-and-white-printing";
    }
    if (jobType == "scan") {
        writeLine("Scanner \"" + processingDeviceName + "\" finished scanning job:");
    } else {
        writeLine("Printer \"" + processingDeviceName + "\" finished " + typestring + " job:");
    }
    writeLine("\t Number: " + std::to_string(jobNR));
    writeLine("\t Submitted by \"" + jobUsername + "\"");
    writeLine("\t " + std::to_string(jobPageCount) + " pages");
}

void OutputStream::writeSystemDiagnosticTitle() {
    writeLine("─────══════ [ System Diagnostic ] ══════─────\n");
}

void OutputStream::writeAdvancedPerDeviceOutput(const std::string &deviceType, const std::string &deviceName,
                                       const std::string &jobQueueString, const std::string &finishedJobsString) {
    std::string deviceTypeLongString;
    if (deviceType == "bw") {
        deviceTypeLongString = " | Black-and-white printer";
    } else if (deviceType == "color") {
        deviceTypeLongString = " | Color printer";
    } else {
        deviceTypeLongString = " | Scanner";
    }
    writeLine("» " + deviceName + deviceTypeLongString);
    writeLine(jobQueueString);
    writeLine(finishedJobsString + "\n");
}

void OutputStream::writeSystemReportHeader() {
    writeLine("╔════════════════ [ System Report ] ════════════════╗\n");
    writeLine("──── Devices ────\n");
}

void OutputStream::writeSystemReportDeviceInfo(const std::string &deviceType, const std::string &deviceName,
                                               const std::string &deviceSpeed, const std::string &deviceCost,
                                               const std::string &deviceEmission) {
    writeLine(deviceName);
    writeLine(deviceType);
    writeLine(deviceSpeed);
    writeLine(deviceCost);
    writeLine(deviceEmission);
}

void OutputStream::writeSystemReportJobInfo(const std::string &jobName, const std::string &jobUser,
                                            const std::string &jobPageCount, const std::string &jobDevice,
                                            const std::string &jobEmission, const std::string &jobCost) {
    writeLine(jobName);
    writeLine(jobUser);
    writeLine(jobPageCount);
    writeLine(jobDevice);
    writeLine(jobEmission);
    writeLine(jobCost + "\n");
}
void OutputStream::writeSystemReportJobsHeader() {
    writeLine("───── Jobs ─────\n");
}

void OutputStream::writeSystemReportNoPendingJobs() {
    writeLine("NO PENDING JOBS\n");
}

void OutputStream::writeSystemReportFooter() {
    writeLine("╚════════════════ [ System Report ] ════════════════╝");
}




