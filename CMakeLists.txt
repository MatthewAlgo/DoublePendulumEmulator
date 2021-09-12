cmake_minimum_required(VERSION 3.0.0)
project(SineWaveEmulator VERSION 0.1.0)

if(WIN32) # IF WE ARE ON WINDOWS

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_TOOLCHAIN_FILE "E:/_WINDOWS_DATA_/VCPKG_PACKAGE_MANAGER/scripts/buildsystems/vcpkg.cmake")

INCLUDE_DIRECTORIES(
    E:/_WINDOWS_DATA_/VCPKG_PACKAGE_MANAGER/installed/x86-windows/include
)

LINK_DIRECTORIES(
    E:/_WINDOWS_DATA_/VCPKG_PACKAGE_MANAGER/installed/x86-windows/lib
)


add_executable(SineWaveEmulator SourceFiles/mainFile.cpp IncludeFiles/helperHeader.h)

# For SFML
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED) # REQUIRED FOR DLL's

TARGET_LINK_LIBRARIES( SineWaveEmulator PRIVATE
    sfml-graphics
    sfml-system
    sfml-audio
    sfml-window
)

ADD_TEST(NAME SineWaveEmulator COMMAND SineWaveEmulator)

INSTALL(TARGETS SineWaveEmulator DESTINATION "Binaries")

endif()