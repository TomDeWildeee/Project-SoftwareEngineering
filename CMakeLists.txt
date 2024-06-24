cmake_minimum_required(VERSION 3.6)
project(Project-SoftwareEngineering)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
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
        PrintingSystemGUI.cpp
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
        Output.cpp
        Utils.cpp
        Tests/InputTest.cpp
        Tests/OutputTest.cpp
        Tests/JobTest.cpp
        Tests/DeviceTest.cpp
        Tests/ManuallyprocessTest.cpp
        Tests/AutomaticallyProcessTest.cpp
        Tests/AdvancedOutputTest.cpp
        Tests/EmissionsTest.cpp
)

# Voor alleen tests deze lijnen commenten
set(CMAKE_PREFIX_PATH "/home/tom/Qt/6.6.3/gcc_64/lib/cmake")
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

set(CMAKE_INSTALL_PREFIX "./build")


# Voor alleen tests deze lijn commenten
add_executable(release_target ${RELEASE_SOURCE_FILES})

add_executable(debug_target ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(debug_target gtest)
# Voor alleen tests deze lijn commenten
target_link_libraries(release_target Qt6::Core Qt6::Widgets Qt6::Gui)
install(TARGETS release_target
        DESTINATION ${CMAKE_INSTALL_PREFIX}
)
