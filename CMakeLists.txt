cmake_minimum_required(VERSION 3.22)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)

# Specify the directory where SFML is located
set(SFML_DIR "${PROJECT_SOURCE_DIR}/lib/SFML")

# Instruct CMake to find the SFML package
find_package(SFML 2.5 COMPONENTS graphics window system)

# Add all your source files
file(GLOB SOURCES "src/*.cpp")

# Define the executable
add_executable(chess ${SOURCES})

# Link SFML to your project
target_link_libraries(chess sfml-graphics sfml-window sfml-system)

# Specify the directories that the compiler should look for include files
include_directories("${PROJECT_SOURCE_DIR}/include")
