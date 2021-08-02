cmake_minimum_required(VERSION 3.15)

project(testsystemc CXX)

set(CMAKE_PREFIX_PATH /opt/systemc-2.3.3/)

find_package(SystemCLanguage CONFIG REQUIRED)

file(GLOB sources
    "*.cpp"
    "modules/*.cpp"
)

add_executable(
    testsystemc
    ${sources}
)

option(LOAD_BALANCING "Use load balancing" OFF) # Enabled by default

if (LOAD_BALANCING)
    add_definitions(-DLOAD_BALANCING)
endif (LOAD_BALANCING)

target_link_libraries(
    testsystemc
    PRIVATE SystemC::systemc
)

set_property(
    TARGET testsystemc
    PROPERTY CXX_STANDARD 11
)