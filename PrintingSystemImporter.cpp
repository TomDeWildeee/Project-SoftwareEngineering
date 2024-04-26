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

bool checkValidnessDeviceProps(const std::string &deviceName, int deviceEmissions, int deviceSpeed, int deviceCost, bool &invalid, OutputStream* outputStream) {
    if (deviceName.empty()) {
        outputStream->writeLine("XML NO INPUT: Expected a string in the <name> attribute but couldn't retrieve it");
        invalid = true;
        return false;
    }

    if (deviceSpeed < 0) {
        outputStream->writeLine("NEGATIVE SPEED INTEGER: Expected a positive integer in the <speed> attribute but got a negative integer instead");
        invalid = true;
        return false;
    }

    if (deviceEmissions < 0) {
        outputStream->writeLine("NEGATIVE EMISSIONS INTEGER: Expected a positive integer in the <emissions> attribute but got a negative integer instead");
        invalid = true;
        return false;
    }

    if (deviceCost < 0) {
        outputStream->writeLine("NEGATIVE COST INTEGER: Expected a positive integer in the <cost> attribute but got a negative integer instead");
        invalid = true;
        return false;
    }
    return true;
}


bool checkValidnessJobProps(const std::string &username, int pageCount, int jobNumber, bool &invalid, OutputStream* outputStream, PrintingSystem &printingSystem) {
    if (username.empty()) {
       outputStream->writeLine("XML NO INPUT: Expected a string in the <userName> attribute but couldn't retrieve it");
        invalid = true;
        return false;
    }

    if (pageCount < 0) {
        outputStream->writeLine("NEGATIVE pageCount INTEGER: Expected a positive integer in the <pageCount> attribute but got a negative integer instead");
        invalid = true;
        return false;
    }

    if (jobNumber < 0) {
        outputStream->writeLine("NEGATIVE jobNumber INTEGER: Expected a positive integer in the <jobNumber> attribute but got a negative integer instead");
        invalid = true;
        return false;
    }

    if (!printingSystem.isUniqueJobNumber(jobNumber)) {
       outputStream->writeLine("NON-UNIQUE JOB NUMBER: Expected a unique jobNumber integer in the <jobNumber> attribute but got a non-unique");
        invalid = true;
        return false;
    }
    return true;
}


ImportEnum PrintingSystemImporter::importPrintingSystem(const char *filename, OutputStream* outputStream, PrintingSystem &printingSystem) {
    REQUIRE(printingSystem.properlyInitialized(), "PrintingSystem wasn't initialized when trying to import the printing system");

    TiXmlDocument doc;

    if (!doc.LoadFile(filename)) {
        outputStream->writeLine("XML IMPORT ABORTED: " + std::string(doc.ErrorDesc()));
        return ImportError;
    }

    TiXmlElement* root = doc.FirstChildElement();
    if (root == nullptr) {
        outputStream->writeLine("Failed to load file: No root element.");
        doc.Clear();
        return ImportError;
    }
    std::string rootName = root->Value();
    if (rootName != "SYSTEM") {
        outputStream->writeLine("XML UNRECOGNIZED ELEMENT: Expected <SYSTEM> ... </SYSTEM> and got <"
        + rootName +  "> ... </" + rootName + ">.");
        doc.Clear();
        return ImportError;
    }

    bool invalid = false;

    for (TiXmlElement* elem = root->FirstChildElement(); elem != nullptr; elem = elem->NextSiblingElement()) {
        std::string elemName = elem->Value();

        if (elemName == "DEVICE") {
            std::string deviceName;
            DeviceType::DeviceTypeEnum deviceType;
            int deviceEmissions, deviceSpeed, deviceCost;

            TiXmlNode* deviceNameNode = elem->FirstChild("name");
            TiXmlNode* deviceEmissionsNode = elem->FirstChild("emissions");
            TiXmlNode* deviceTypeNode = elem->FirstChild("type");
            TiXmlNode* deviceSpeedNode = elem->FirstChild("speed");
            TiXmlNode* deviceCostNode = elem->FirstChild("cost");

            // Check if deviceNameNode is present in the XML file
            if (deviceNameNode == nullptr) {
                outputStream->writeLine("XML UNRECOGNIZED ATTRIBUTE: Expected <name> ... </name>");
                invalid = true;
                continue;

            } else {
                deviceName = getTextFromNode(deviceNameNode);
            }

            // Check if deviceEmissionsNode is present in the XML file
            if (deviceEmissionsNode == nullptr) {
                outputStream->writeLine("XML UNRECOGNIZED ATTRIBUTE: Expected <emissions> ... </emissions>");
                invalid = true;
                continue;

            } else {
                std::string deviceEmissionsString = getTextFromNode(deviceEmissionsNode);
                if (deviceEmissionsString.empty()) {
                    outputStream->writeLine("XML NO INPUT: Expected an integer in the <emissions> attribute but couldn't retrieve it");
                    invalid = true;
                    continue;
                }

                if (!isNumber(deviceEmissionsString)) {
                    outputStream->writeLine("XML INVALID VALUE: Expected an integer in the <emissions> attribute but got a different type");
                    invalid = true;
                    continue;
                } else {
                    deviceEmissions = std::stoi(deviceEmissionsString);
                }

            }

            // Check if deviceTypeNode is present in the XML file
            if (deviceTypeNode == nullptr) {
                outputStream->writeLine("XML UNRECOGNIZED ATTRIBUTE: Expected <type> ... </type>");
                invalid = true;
                continue;

            } else {
                std::string deviceTypeString = getTextFromNode(deviceTypeNode);
                if (deviceTypeString.empty()) {
                    outputStream->writeLine("XML NO INPUT: Expected either bw or color in the <type> attribute but couldn't retrieve it");
                    invalid = true;
                    continue;
                }

                if (deviceTypeString == "color") {
                    deviceType = DeviceType::color;
                } else if (deviceTypeString == "bw") {
                    deviceType = DeviceType::bw;
                } else {
                    outputStream->writeLine("XML NO INPUT: Expected either bw or color in the <type> attribute but couldn't retrieve it");
                    invalid = true;
                    continue;
                }
            }

            // Check if deviceSpeedNode is present in the XML file
            if (deviceSpeedNode == nullptr) {
                outputStream->writeLine("XML UNRECOGNIZED ATTRIBUTE: Expected <speed> ... </speed>");
                invalid = true;
                continue;

            } else {
                std::string deviceSpeedString = getTextFromNode(deviceSpeedNode);
                if (deviceSpeedString.empty()) {
                    outputStream->writeLine("XML NO INPUT: Expected an integer in the <speed> attribute but couldn't retrieve it");
                    invalid = true;
                    continue;
                }

                if (!isNumber(deviceSpeedString)) {
                    outputStream->writeLine("XML INVALID VALUE: Expected an integer in the <speed> attribute but got a different type");
                    invalid = true;
                    continue;
                } else {
                    deviceSpeed = std::stoi(deviceSpeedString);
                }
            }

            //Check if deviceCostNode is present in the XML file
            if (deviceCostNode == nullptr) {
                outputStream ->writeLine("XML INVALID COST: Expected <cost> ... </cost>");
                invalid = true;
                continue;

            } else {
                std::string deviceCostString = getTextFromNode(deviceCostNode);
                if (deviceCostString.empty()) {
                    outputStream->writeLine("XML NO INPUT: Expected an integer in the <cost> attribute but couldn't retrieve it");
                    invalid = true;
                    continue;
                }

                if (!isNumber(deviceCostString)) {
                    outputStream->writeLine("XML INVALID VALUE: Expected an integer in the <cost> attribute but got a different type");
                    invalid = true;
                    continue;
                } else {
                    deviceCost = std::stoi(deviceCostString);
                }
            }

            bool validDeviceProperties = checkValidnessDeviceProps(deviceName, deviceEmissions, deviceSpeed, deviceCost, invalid, outputStream);
            if (!validDeviceProperties) continue;

            auto* newDevice = new Device(deviceName, deviceEmissions, deviceSpeed, deviceType, deviceCost/100);
            printingSystem.addDevice(newDevice);

        } else if (elemName == "JOB") {
            int jobNumber, pageCount;
            std::string username;
            JobType::JobTypeEnum jobType;

            TiXmlNode* jobNumberNode = elem->FirstChild("jobNumber");
            TiXmlNode* pageCountNode = elem->FirstChild("pageCount");
            TiXmlNode* jobTypeNode = elem->FirstChild("type");
            TiXmlNode* userNameNode = elem->FirstChild("userName");

            if (userNameNode == nullptr) {
                outputStream->writeLine("XML UNRECOGNIZED ATTRIBUTE: Expected <userName> ... </userName>");
                invalid = true;
                continue;
            } else {
                username = getTextFromNode(userNameNode);
            }

            if (jobNumberNode == nullptr) {
                outputStream->writeLine("XML UNRECOGNIZED ATTRIBUTE: Expected <jobNumber> ... </jobNumber>");
                invalid = true;
                continue;

            } else {
                std::string jobNumberString = getTextFromNode(jobNumberNode);

                if (jobNumberString.empty()) {
                    outputStream->writeLine("XML NO INPUT: Expected an integer in the <jobNumber> attribute but couldn't retrieve it");
                    invalid = true;
                    continue;
                }

                if (!isNumber(jobNumberString)) {
                    outputStream->writeLine("XML INVALID VALUE: Expected an integer in the <jobNumber> attribute but got a different type");
                    invalid = true;
                    continue;
                } else {
                    jobNumber = std::stoi(jobNumberString);
                }
            }

            if (pageCountNode == nullptr) {
                outputStream->writeLine("XML UNRECOGNIZED ATTRIBUTE: Expected <pageCount> ... </pageCount>");
                invalid = true;
                continue;
            } else {
                std::string pageCountString = getTextFromNode(pageCountNode);

                if (pageCountString.empty()) {
                    outputStream->writeLine("XML NO INPUT: Expected an integer in the <pageCount> attribute but couldn't retrieve it");
                    invalid = true;
                    continue;
                }

                if (!isNumber(pageCountString)) {
                    outputStream->writeLine("XML INVALID VALUE: Expected an integer in the <pageCount> attribute but got a different type");
                    invalid = true;
                    continue;
                } else {
                    pageCount = std::stoi(pageCountString);
                }
            }

            if (jobTypeNode == nullptr) {
                outputStream->writeLine("XML UNRECOGNIZED ATTRIBUTE: Expected <type> ... </type>");
                invalid = true;
                continue;

            } else {
                std::string jobTypeString = getTextFromNode(jobTypeNode);
                if (jobTypeString.empty()) {
                    outputStream->writeLine("XML NO INPUT: Expected either bw or color in the <type> attribute but couldn't retrieve it");
                    invalid = true;
                    continue;
                }

                if (jobTypeString == "color") {
                    jobType = JobType::color;
                } else if (jobTypeString == "bw") {
                    jobType = JobType::bw;
                } else {
                    outputStream->writeLine("XML NO INPUT: Expected either bw or color in the <type> attribute but couldn't retrieve it");
                    invalid = true;
                    continue;
                }
            }

            bool validJobProperties = checkValidnessJobProps(username, pageCount, jobNumber, invalid, outputStream, printingSystem);
            if (!validJobProperties) continue;

            auto* newJob = new Job(jobNumber, pageCount, username, jobType);
            printingSystem.addJob(newJob);

        } else {
            outputStream->writeLine("XML UNRECOGNIZED ELEMENT: Expected <DEVICE> ... </DEVICE> or <JOB> ... </JOB>.");
            invalid = true;
        }
    }

    if (invalid) {
        outputStream->writeLine("XML NOT CONSISTENT: XML file was not consistent and is invalid, system will be cleared");
        printingSystem.clearSystemBecauseInvalid();
        doc.Clear();
        return ImportError;
    }

    doc.Clear();
    return ImportSuccess;
}
