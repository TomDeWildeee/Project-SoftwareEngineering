#include <iostream>
#include "PrintingSystemImporter.h"
#include "tinyxml/tinyxml.h"
#include "DesignByContract.h"
#include "Utils.h"

std::string getTextFromNode(TiXmlNode* node) {
    TiXmlNode* childNode = node->FirstChild();
    if (childNode == nullptr) return "";
    TiXmlText* text = childNode->ToText();
    if (text == nullptr) return "";
    return text->Value();
}

bool checkValidnessDeviceProps(const std::string &deviceName, int deviceEmissions, int deviceSpeed, bool &invalid, std::ostream &errStream) {
    if (deviceName.empty()) {
        errStream << "XML NO INPUT: Expected a string in the <name> attribute but couldn't retrieve it" << std::endl;
        invalid = true;
        return false;
    }

    if (deviceSpeed < 0) {
        errStream << "NEGATIVE SPEED INTEGER: Expected a positive integer in the <speed> attribute but got a negative integer instead" << std::endl;
        invalid = true;
        return false;
    }

    if (deviceEmissions < 0) {
        errStream << "NEGATIVE EMISSIONS INTEGER: Expected a positive integer in the <emissions> attribute but got a negative integer instead" << std::endl;
        invalid = true;
        return false;
    }
    return true;
}


bool checkValidnessJobProps(const std::string &username, int pageCount, int jobNumber, bool &invalid, std::ostream &errStream, PrintingSystem &printingSystem) {
    if (username.empty()) {
        errStream << "XML NO INPUT: Expected a string in the <name> attribute but couldn't retrieve it" << std::endl;
        invalid = true;
        return false;
    }

    if (pageCount < 0) {
        errStream << "NEGATIVE SPEED INTEGER: Expected a positive integer in the <speed> attribute but got a negative integer instead" << std::endl;
        invalid = true;
        return false;
    }

    if (jobNumber < 0) {
        errStream << "NEGATIVE EMISSIONS INTEGER: Expected a positive integer in the <emissions> attribute but got a negative integer instead" << std::endl;
        invalid = true;
        return false;
    }

    if (!printingSystem.isUniqueJobNumber(jobNumber)) {
        errStream << "NON-UNIQUE JOB NUMBER: Expected a unique jobNumber integer in the <jobNumber> attribute but got a non-unique" << std::endl;
        invalid = true;
        return false;
    }
    return true;
}


ImportEnum PrintingSystemImporter::importPrintingSystem(const char *filename, std::ostream &errStream, PrintingSystem &printingSystem) {
    REQUIRE(printingSystem.properlyInitialized(), "PrintingSystem wasn't initialized when trying to import the printing system");

    TiXmlDocument doc;

    if (!doc.LoadFile(filename)) {
        errStream << "XML IMPORT ABORTED: " << doc.ErrorDesc() << std::endl;
        return ImportError;
    }

    TiXmlElement* root = doc.FirstChildElement();
    if (root == nullptr) {
        errStream << "Failed to load file: No root element." << std::endl;
        doc.Clear();
        return ImportError;
    }

    std::string rootName = root->Value();
    if (rootName != "SYSTEM") {
        errStream << "XML UNRECOGNIZED ELEMENT: Expected <SYSTEM> ... </SYSTEM> and got <"
                  << rootName <<  "> ... </" << rootName << ">." << std::endl;
        doc.Clear();
        return ImportError;
    }

    bool invalid = false;

    for (TiXmlElement* elem = root->FirstChildElement(); elem != nullptr; elem = elem->NextSiblingElement()) {
        std::string elemName = elem->Value();

        if (elemName == "DEVICE") {
            std::string deviceName;
            int deviceEmissions, deviceSpeed;

            TiXmlNode* deviceNameNode = elem->FirstChild("name");
            TiXmlNode* deviceEmissionsNode = elem->FirstChild("emissions");
            TiXmlNode* deviceSpeedNode = elem->FirstChild("speed");

            // Check if deviceNameNode is present in the XML file
            if (deviceNameNode == nullptr) {
                errStream << "XML UNRECOGNIZED ATTRIBUTE: Expected <name> ... </name>" << std::endl;
                invalid = true;
                continue;

            } else {
                deviceName = getTextFromNode(deviceNameNode);
            }

            // Check if deviceEmissionsNode is present in the XML file
            if (deviceEmissionsNode == nullptr) {
                errStream << "XML UNRECOGNIZED ATTRIBUTE: Expected <emissions> ... </emissions>" << std::endl;
                invalid = true;
                continue;

            } else {
                std::string deviceEmissionsString = getTextFromNode(deviceEmissionsNode);
                if (deviceEmissionsString.empty()) {
                    errStream << "XML NO INPUT: Expected an integer in the <emissions> attribute but couldn't retrieve it" << std::endl;
                    invalid = true;
                    continue;
                }

                if (!isNumber(deviceEmissionsString)) {
                    errStream << "XML INVALID VALUE: Expected an integer in the <emissions> attribute but got a different type" << std::endl;
                    invalid = true;
                    continue;
                } else {
                    deviceEmissions = std::stoi(deviceEmissionsString);
                }
            }


            // Check if deviceSpeedNode is present in the XML file
            if (deviceSpeedNode == nullptr) {
                errStream << "XML UNRECOGNIZED ATTRIBUTE: Expected <speed> ... </speed>" << std::endl;
                invalid = true;
                continue;

            } else {
                std::string deviceSpeedString = getTextFromNode(deviceSpeedNode);
                if (deviceSpeedString.empty()) {
                    errStream << "XML NO INPUT: Expected an integer in the <speed> attribute but couldn't retrieve it" << std::endl;
                    invalid = true;
                    continue;
                }

                if (!isNumber(deviceSpeedString)) {
                    errStream << "XML INVALID VALUE: Expected an integer in the <speed> attribute but got a different type" << std::endl;
                    invalid = true;
                    continue;
                } else {
                    deviceSpeed = std::stoi(deviceSpeedString);
                }
            }

            bool validDeviceProperties = checkValidnessDeviceProps(deviceName, deviceEmissions, deviceSpeed, invalid, errStream);
            if (!validDeviceProperties) continue;

            auto* newDevice = new Device(deviceName, deviceEmissions, deviceSpeed);
            printingSystem.addDevice(newDevice);

        } else if (elemName == "JOB") {
            int jobNumber, pageCount;
            std::string username;

            TiXmlNode* jobNumberNode = elem->FirstChild("jobNumber");
            TiXmlNode* pageCountNode = elem->FirstChild("pageCount");
            TiXmlNode* userNameNode = elem->FirstChild("userName");

            if (userNameNode == nullptr) {
                errStream << "XML UNRECOGNIZED ATTRIBUTE: Expected <userName> ... </userName>" << std::endl;
                invalid = true;
                continue;
            } else {
                username = getTextFromNode(userNameNode);
            }

            if (jobNumberNode == nullptr) {
                errStream << "XML UNRECOGNIZED ATTRIBUTE: Expected <jobNumber> ... </jobNumber>" << std::endl;
                invalid = true;
                continue;

            } else {
                std::string jobNumberString = getTextFromNode(jobNumberNode);

                if (jobNumberString.empty()) {
                    errStream << "XML NO INPUT: Expected an integer in the <jobNumber> attribute but couldn't retrieve it" << std::endl;
                    invalid = true;
                    continue;
                }

                if (!isNumber(jobNumberString)) {
                    errStream << "XML INVALID VALUE: Expected an integer in the <jobNumber> attribute but got a different type" << std::endl;
                    invalid = true;
                    continue;
                } else {
                    jobNumber = std::stoi(jobNumberString);
                }
            }

            if (pageCountNode == nullptr) {
                errStream << "XML UNRECOGNIZED ATTRIBUTE: Expected <pageCount> ... </pageCount>" << std::endl;
                invalid = true;
                continue;
            } else {
                std::string pageCountString = getTextFromNode(pageCountNode);

                if (pageCountString.empty()) {
                    errStream << "XML NO INPUT: Expected an integer in the <pageCount> attribute but couldn't retrieve it" << std::endl;
                    invalid = true;
                    continue;
                }

                if (!isNumber(pageCountString)) {
                    errStream << "XML INVALID VALUE: Expected an integer in the <pageCount> attribute but got a different type" << std::endl;
                    invalid = true;
                    continue;
                } else {
                    pageCount = std::stoi(pageCountString);
                }
            }

            bool validJobProperties = checkValidnessJobProps(username, pageCount, jobNumber, invalid, errStream, printingSystem);
            if (!validJobProperties) continue;

            auto* newJob = new Job(jobNumber, pageCount, username);
            printingSystem.addJob(newJob);

        } else {
            errStream << "XML UNRECOGNIZED ELEMENT: Expected <DEVICE> ... </DEVICE> or <JOB> ... </JOB>." << std::endl;
            invalid = true;
        }
    }

    if (invalid) {
        errStream << "XML NOT CONSISTENT: XML file was not consistent and is invalid, system will be cleared" << std::endl;
        printingSystem.clearSystemBecauseInvalid();
        doc.Clear();
        return ImportError;
    }

    doc.Clear();
    return ImportSuccess;
}
