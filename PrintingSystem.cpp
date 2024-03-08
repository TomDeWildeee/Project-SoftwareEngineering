#include "DesignByContract.h"
#include "PrintingSystem.h"
#include "tinyxml.h"

bool PrintingSystem::properlyInitialized() {
    return _initCheck == this;
}

PrintingSystem::PrintingSystem() {
    _initCheck = this;
    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

std::string getTextFromNode(TiXmlNode* node) {
    TiXmlNode* childNode = node->FirstChild();
    if (childNode == nullptr) return "";
    TiXmlText* text = childNode->ToText();
    if (text == nullptr) return "";
    return text->Value();
}

ImportEnum PrintingSystem::importPrintingSystem(const char* filename, std::ostream &errStream) {
    REQUIRE(this->properlyInitialized(), "PrintingSystem wasn't initialized when trying to import the printing system");

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

    for (TiXmlElement* elem = root->FirstChildElement(); elem != nullptr; elem = elem->NextSiblingElement()) {
        std::string elemName = elem->Value();
        if (elemName == "DEVICE") {
            std::string deviceName;
            int deviceEmissions, deviceSpeed;

            TiXmlNode* deviceNameNode = elem->FirstChild("name");
            TiXmlNode* deviceEmissionsNode = elem->FirstChild("emissions");
            TiXmlNode* deviceSpeedNode = elem->FirstChild("speed");

            if (deviceNameNode == nullptr) {
                errStream << "XML UNRECOGNIZED ATTRIBUTE: Expected <name> ... </name>" << std::endl;
                continue;
            } else {
                deviceName = getTextFromNode(deviceNameNode);
            }

            if (deviceEmissionsNode == nullptr) {
                errStream << "XML UNRECOGNIZED ATTRIBUTE: Expected <emissions> ... </emissions>" << std::endl;
                continue;
            } else {
                std::string deviceEmissionsString = getTextFromNode(deviceEmissionsNode);
                if (deviceEmissionsString.empty()) {
                    errStream << "XML NO INPUT: Expected an integer in the <emissions> attribute but couldn't retrieve it" << std::endl;
                    continue;
                }
                deviceEmissions = std::stoi(deviceEmissionsString);
            }

            if (deviceSpeedNode == nullptr) {
                errStream << "XML UNRECOGNIZED ATTRIBUTE: Expected <speed> ... </speed>" << std::endl;
                continue;
            } else {
                std::string deviceSpeedString = getTextFromNode(deviceSpeedNode);
                if (deviceSpeedString.empty()) {
                    errStream << "XML NO INPUT: Expected an integer in the <speed> attribute but couldn't retrieve it" << std::endl;
                    continue;
                }
                deviceSpeed = std::stoi(deviceSpeedString);
            }

            if (deviceName.empty()) {
                errStream << "XML NO INPUT: Expected a string in the <name> attribute but couldn't retrieve it" << std::endl;
                continue;
            }

            if (deviceSpeed < 0) {
                errStream << "NEGATIVE SPEED INTEGER: Expected a positive integer in the <speed> attribute but got a negative integer instead" << std::endl;
                continue;
            }

            if (deviceEmissions < 0) {
                errStream << "NEGATIVE EMISSIONS INTEGER: Expected a positive integer in the <emissions> attribute but got a negative integer instead" << std::endl;
                continue;
            }

            std::cout << deviceName << " | " << deviceSpeed << " | " << deviceEmissions << std::endl;

        } else if (elemName == "JOB") {
            // TODO
        } else {
            errStream << "XML UNRECOGNIZED ELEMENT: Expected <DEVICE> ... </DEVICE> or <JOB> ... </JOB>." << std::endl;
        }
    }
    return ImportSuccess;
}
