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
        outputStream->writeXMLNoInput("a string", "<name>");
        invalid = true;
        return false;
    }

    if (deviceSpeed < 0) {
        outputStream->writeXMLNegativeInteger("SPEED", "<speed>");
        invalid = true;
        return false;
    }

    if (deviceEmissions < 0) {
        outputStream->writeXMLNegativeInteger("EMISSIONS", "<emissions>");
        invalid = true;
        return false;
    }

    if (deviceCost < 0) {
        outputStream->writeXMLNegativeInteger("COST", "<cost>");
        invalid = true;
        return false;
    }
    return true;
}


bool checkValidnessJobProps(const std::string &username, int pageCount, int jobNumber, bool &invalid, OutputStream* outputStream, PrintingSystem &printingSystem) {
    if (username.empty()) {
        outputStream->writeXMLNoInput("a string", "<userName>");
        invalid = true;
        return false;
    }

    if (pageCount < 0) {
        outputStream->writeXMLNegativeInteger("pageCount", "<pageCount>");
        invalid = true;
        return false;
    }

    if (jobNumber < 0) {
        outputStream->writeXMLNegativeInteger("jobNumber", "<jobNumber>");
        invalid = true;
        return false;
    }

    if (!printingSystem.isUniqueJobNumber(jobNumber)) {
        outputStream->writeXMLNonUniqueNumber("JOB NUMBER", "jobNumber", "<jobNumber>");
        invalid = true;
        return false;
    }
    return true;
}


ImportEnum PrintingSystemImporter::importPrintingSystem(const char *filename, OutputStream* outputStream, PrintingSystem &printingSystem) {
    REQUIRE(printingSystem.properlyInitialized(), "PrintingSystem wasn't initialized when trying to import the printing system");

    TiXmlDocument doc;

    if (!doc.LoadFile(filename)) {
        outputStream->writeXMLAborted(std::string(doc.ErrorDesc()));
        return ImportError;
    }

    TiXmlElement* root = doc.FirstChildElement();
    if (root == nullptr) {
        outputStream->writeXMLFailedToLoadFile();
        doc.Clear();
        return ImportError;
    }
    std::string rootName = root->Value();
    if (rootName != "SYSTEM") {
        outputStream->writeXMLUnrecognizedElement("SYSTEM", rootName);
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
                outputStream->writeXMLUnrecognizedAttribute("name");
                invalid = true;
                continue;

            } else {
                deviceName = getTextFromNode(deviceNameNode);
            }

            // Check if deviceEmissionsNode is present in the XML file
            if (deviceEmissionsNode == nullptr) {
                outputStream->writeXMLUnrecognizedAttribute("emissions");
                invalid = true;
                continue;

            } else {
                std::string deviceEmissionsString = getTextFromNode(deviceEmissionsNode);
                if (deviceEmissionsString.empty()) {
                    outputStream->writeXMLNoInput("an integer", "<emissions>");
                    invalid = true;
                    continue;
                }

                if (!isNumber(deviceEmissionsString)) {
                    outputStream->writeXMLInvalidValueType("an integer", "<emissions>");
                    invalid = true;
                    continue;
                } else {
                    deviceEmissions = std::stoi(deviceEmissionsString);
                }

            }

            // Check if deviceTypeNode is present in the XML file
            if (deviceTypeNode == nullptr) {
                outputStream->writeXMLUnrecognizedAttribute("type");
                invalid = true;
                continue;

            } else {
                std::string deviceTypeString = getTextFromNode(deviceTypeNode);
                if (deviceTypeString.empty()) {
                    outputStream->writeXMLNoInput("either bw, color or scan", "<type>");
                    invalid = true;
                    continue;
                }

                if (deviceTypeString == "color") {
                    deviceType = DeviceType::color;
                } else if (deviceTypeString == "bw") {
                    deviceType = DeviceType::bw;
                } else if (deviceTypeString == "scan") {
                    deviceType = DeviceType::scan;
                } else {
                    outputStream->writeXMLNoInput("either bw, color or scan", "<type>");
                    invalid = true;
                    continue;
                }
            }
            if(deviceType == DeviceType::color && deviceEmissions > 23){
                outputStream->writeXMLInvalidEmissions("color", "23g/page", std::to_string(deviceEmissions));
                invalid = true;
                continue;
            }else if(deviceType == DeviceType::bw && deviceEmissions > 8){
                outputStream->writeXMLInvalidEmissions("black & white", "8g/page", std::to_string(deviceEmissions));
                invalid = true;
                continue;
            }else if(deviceType == DeviceType::scan && deviceEmissions > 12){
                outputStream->writeXMLInvalidEmissions("scan", "12g/page", std::to_string(deviceEmissions));
                invalid = true;
                continue;
            }
            // Check if deviceSpeedNode is present in the XML file
            if (deviceSpeedNode == nullptr) {
                outputStream->writeXMLUnrecognizedAttribute("speed");
                invalid = true;
                continue;

            } else {
                std::string deviceSpeedString = getTextFromNode(deviceSpeedNode);
                if (deviceSpeedString.empty()) {
                    outputStream->writeXMLNoInput("an integer", "<speed>");
                    invalid = true;
                    continue;
                }

                if (!isNumber(deviceSpeedString)) {
                    outputStream->writeXMLInvalidValueType("an integer", "<speed>");
                    invalid = true;
                    continue;
                } else {
                    deviceSpeed = std::stoi(deviceSpeedString);
                }
            }

            //Check if deviceCostNode is present in the XML file
            if (deviceCostNode == nullptr) {
                outputStream->writeXMLInvalidCost();
                invalid = true;
                continue;

            } else {
                std::string deviceCostString = getTextFromNode(deviceCostNode);
                if (deviceCostString.empty()) {
                    outputStream->writeXMLNoInput("a float", "<cost>");
                    invalid = true;
                    continue;
                }

                if (!isFloat(deviceCostString)) {
                    outputStream->writeXMLInvalidValueType("a float", "<cost>");
                    invalid = true;
                    continue;
                } else {
                    deviceCost = std::stoi(deviceCostString);
                }
            }

            bool validDeviceProperties = checkValidnessDeviceProps(deviceName, deviceEmissions, deviceSpeed, deviceCost, invalid, outputStream);
            if (!validDeviceProperties) continue;

            Device* newDevice;

            if (deviceType == DeviceType::color) {
                newDevice = new ColorPrinter(deviceName, deviceEmissions, deviceSpeed, deviceCost);
            } else if (deviceType == DeviceType::bw) {
                newDevice = new BWPrinter(deviceName, deviceEmissions, deviceSpeed, deviceCost);
            } else {
                newDevice = new Scanner(deviceName, deviceEmissions, deviceSpeed, deviceCost);
            }

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
                outputStream->writeXMLUnrecognizedAttribute("userName");
                invalid = true;
                continue;
            } else {
                username = getTextFromNode(userNameNode);
            }

            if (jobNumberNode == nullptr) {
                outputStream->writeXMLUnrecognizedAttribute("jobNumber");
                invalid = true;
                continue;

            } else {
                std::string jobNumberString = getTextFromNode(jobNumberNode);

                if (jobNumberString.empty()) {
                    outputStream->writeXMLNoInput("an integer", "<jobNumber>");
                    invalid = true;
                    continue;
                }

                if (!isNumber(jobNumberString)) {
                    outputStream->writeXMLInvalidValueType("an integer", "<jobNumber>");
                    invalid = true;
                    continue;
                } else {
                    jobNumber = std::stoi(jobNumberString);
                }
            }

            if (pageCountNode == nullptr) {
                outputStream->writeXMLUnrecognizedAttribute("pageCount");
                invalid = true;
                continue;
            } else {
                std::string pageCountString = getTextFromNode(pageCountNode);

                if (pageCountString.empty()) {
                    outputStream->writeXMLNoInput("an integer", "<pageCount>");
                    invalid = true;
                    continue;
                }

                if (!isNumber(pageCountString)) {
                    outputStream->writeXMLInvalidValueType("an integer", "<pageCount>");
                    invalid = true;
                    continue;
                } else {
                    pageCount = std::stoi(pageCountString);
                }
            }

            if (jobTypeNode == nullptr) {
                outputStream->writeXMLUnrecognizedAttribute("type");
                invalid = true;
                continue;

            } else {
                std::string jobTypeString = getTextFromNode(jobTypeNode);
                if (jobTypeString.empty()) {
                    outputStream->writeXMLNoInput("either bw, color or scan", "<type>");
                    invalid = true;
                    continue;
                }

                if (jobTypeString == "color") {
                    jobType = JobType::color;
                } else if (jobTypeString == "bw") {
                    jobType = JobType::bw;
                } else if (jobTypeString == "scan") {
                    jobType = JobType::scan;
                } else {
                    outputStream->writeXMLNoInput("either bw, color or scan", "<type>");
                    invalid = true;
                    continue;
                }
            }

            bool validJobProperties = checkValidnessJobProps(username, pageCount, jobNumber, invalid, outputStream, printingSystem);
            if (!validJobProperties) continue;

            Job* newJob;
            if (jobType == JobType::color) {
                newJob = new ColorJob(jobNumber, pageCount, username);
            } else if (jobType == JobType::bw) {
                newJob = new BWJob(jobNumber, pageCount, username);
            } else {
                newJob = new ScanJob(jobNumber, pageCount, username);
            }

            printingSystem.addJob(newJob);

        } else {
            outputStream->writeXMLUnrecognizedElementExpectedDeviceOrJob();
            invalid = true;
        }
    }

    if (invalid) {
        outputStream->writeXMLNotConsistent();
        printingSystem.clearSystemBecauseInvalid();
        doc.Clear();
        return ImportError;
    }
    printingSystem.queueJobs();
    doc.Clear();
    return ImportSuccess;
}
