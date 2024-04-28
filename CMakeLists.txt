cmake_minimum_required(VERSION 3.6)
project(Project-SoftwareEngineering)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 17)
# Remove the "-O2" flag if you have problems with the debugger.
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Werror -O2")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(./gtest/include)

# Set Library dir
link_directories(./gtest/lib)

# Set source files for RELEASE target
# Only add cpp files, no h files!
# Only add files with functionality here, no test files!
set(RELEASE_SOURCE_FILES
        PrintingSystem.cpp
        PrintingSystemImporter.cpp
        Device.cpp
        Job.cpp
        tinyxml/tinystr.cpp
        tinyxml/tinyxml.cpp
        tinyxml/tinyxmlerror.cpp
        tinyxml/tinyxmlparser.cpp
        PrintingSystemMain.cpp
        Utils.cpp
        Output.cpp
)

# Set source files for DEBUG target
# Only add cpp files, no h files!
set(DEBUG_SOURCE_FILES
        Tests/tests.cpp
        PrintingSystemImporter.cpp
        PrintingSystem.cpp
        Device.cpp
        Job.cpp
        tinyxml/tinystr.cpp
        tinyxml/tinyxml.cpp
        tinyxml/tinyxmlerror.cpp
        tinyxml/tinyxmlparser.cpp
        Tests/InputTest.cpp
        Utils.cpp
        Tests/OutputTest.cpp
        Tests/JobTest.cpp
        Tests/DeviceTest.cpp
        Tests/ManuallyprocessTest.cpp
        Tests/AutomaticallyProcessTest.cpp
        Output.cpp
        Tests/AdvancedOutputTest.cpp
        Tests/EmissionsTest.cpp
)

# Create RELEASE target
add_executable(release_target ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(debug_target ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(debug_target gtest)
