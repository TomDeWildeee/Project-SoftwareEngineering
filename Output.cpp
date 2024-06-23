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
    REQUIRE(this->properlyInitialized(), "OutputStream wasn't initialized when writing this string");
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
    REQUIRE(this->properlyInitialized(), "OutputStream wasn't initialized when writing this string");
    writeLine("─────══════ [ System Diagnostic ] ══════─────\n");
}

void OutputStream::writeAdvancedPerDeviceOutput(const std::string &deviceType, const std::string &deviceName,
                                       const std::string &jobQueueString, const std::string &finishedJobsString) {
    REQUIRE(this->properlyInitialized(), "OutputStream wasn't initialized when writing this string");
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
    REQUIRE(this->properlyInitialized(), "OutputStream wasn't initialized when writing this string");
    writeLine("╔════════════════ [ System Report ] ════════════════╗\n");
    writeLine("──── Devices ────\n");
}

void OutputStream::writeSystemReportDeviceInfo(const std::string &deviceType, const std::string &deviceName,
                                               const std::string &deviceSpeed, const std::string &deviceCost,
                                               const std::string &deviceEmission) {
    REQUIRE(this->properlyInitialized(), "OutputStream wasn't initialized when writing this string");
    writeLine(deviceName);
    writeLine(deviceType);
    writeLine(deviceSpeed);
    writeLine(deviceCost);
    writeLine(deviceEmission);
}

void OutputStream::writeSystemReportJobInfo(const std::string &jobName, const std::string &jobUser,
                                            const std::string &jobPageCount, const std::string &jobDevice,
                                            const std::string &jobEmission, const std::string &jobCost) {
    REQUIRE(this->properlyInitialized(), "OutputStream wasn't initialized when writing this string");
    writeLine(jobName);
    writeLine(jobUser);
    writeLine(jobPageCount);
    writeLine(jobDevice);
    writeLine(jobEmission);
    writeLine(jobCost + "\n");
}
void OutputStream::writeSystemReportJobsHeader() {
    REQUIRE(this->properlyInitialized(), "OutputStream wasn't initialized when writing this string");
    writeLine("───── Jobs ─────\n");
}

void OutputStream::writeSystemReportNoPendingJobs() {
    REQUIRE(this->properlyInitialized(), "OutputStream wasn't initialized when writing this string");
    writeLine("NO PENDING JOBS\n");
}

void OutputStream::writeSystemReportFooter() {
    REQUIRE(this->properlyInitialized(), "OutputStream wasn't initialized when writing this string");
    writeLine("╚════════════════ [ System Report ] ════════════════╝");
}

// XML Error writing

void OutputStream::writeXMLAborted(const std::string &errorDesc) {
    REQUIRE(this->properlyInitialized(), "OutputStream wasn't initialized when writing this string");
    writeLine("XML IMPORT ABORTED: " + errorDesc);
}

void OutputStream::writeXMLFailedToLoadFile() {
    REQUIRE(this->properlyInitialized(), "OutputStream wasn't initialized when writing this string");
    writeLine("Failed to load file: No root element.");
}

void OutputStream::writeXMLUnrecognizedElement(const std::string &expected, const std::string &got) {
    REQUIRE(this->properlyInitialized(), "OutputStream wasn't initialized when writing this string");
    writeLine("XML UNRECOGNIZED ELEMENT: Expected <" + expected + "> ... </" + expected + "> and got <"
                            + got + "> ... </" + got + ">.");
}

void OutputStream::writeXMLUnrecognizedAttribute(const std::string &expected) {
    REQUIRE(this->properlyInitialized(), "OutputStream wasn't initialized when writing this string");
    writeLine("XML UNRECOGNIZED ATTRIBUTE: Expected <" + expected + "> ... </" + expected + ">");
}

void OutputStream::writeXMLNoInput(const std::string &what, const std::string &attributeTag) {
    REQUIRE(this->properlyInitialized(), "OutputStream wasn't initialized when writing this string");
    writeLine("XML NO INPUT: Expected " + what + " in the " + attributeTag + " attribute but couldn't retrieve it");
}

void OutputStream::writeXMLNegativeInteger(const std::string &type, const std::string &attributeTag) {
    REQUIRE(this->properlyInitialized(), "OutputStream wasn't initialized when writing this string");
    writeLine("NEGATIVE " + type + " INTEGER: Expected a positive integer in the "
    + attributeTag + " attribute but got a negative integer instead");
}

void OutputStream::writeXMLNonUniqueNumber(const std::string &type, const std::string &lowerType, const std::string &attributeTag) {
    REQUIRE(this->properlyInitialized(), "OutputStream wasn't initialized when writing this string");
    writeLine("NON-UNIQUE " + type + ": Expected a unique " + lowerType + " integer in the "
    + attributeTag + " attribute but got a non-unique");
}

void OutputStream::writeXMLInvalidValueType(const std::string &type, const std::string &attributeTag) {
    REQUIRE(this->properlyInitialized(), "OutputStream wasn't initialized when writing this string");
    writeLine("XML INVALID VALUE: Expected " + type + " in the " + attributeTag + " attribute but got a different type");
}

void OutputStream::writeXMLInvalidEmissions(const std::string &typePrinter, const std::string &gramsPerPage,
                                            const std::string &got) {
    REQUIRE(this->properlyInitialized(), "OutputStream wasn't initialized when writing this string");
    writeLine("XML INVALID VALUE: Emissions cap for " + typePrinter + " is " + gramsPerPage + ", but got " + got);
}

void OutputStream::writeXMLInvalidCost() {
    REQUIRE(this->properlyInitialized(), "OutputStream wasn't initialized when writing this string");
    writeLine("XML INVALID COST: Expected <cost> ... </cost>");
}

void OutputStream::writeXMLUnrecognizedElementExpectedDeviceOrJob() {
    REQUIRE(this->properlyInitialized(), "OutputStream wasn't initialized when writing this string");
    writeLine("XML UNRECOGNIZED ELEMENT: Expected <DEVICE> ... </DEVICE> or <JOB> ... </JOB>.");
}

void OutputStream::writeXMLNotConsistent() {
    REQUIRE(this->properlyInitialized(), "OutputStream wasn't initialized when writing this string");
    writeLine("XML NOT CONSISTENT: XML file was not consistent and is invalid, system will be cleared");
}
