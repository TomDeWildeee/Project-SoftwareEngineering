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
