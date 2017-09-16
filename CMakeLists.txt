cmake_minimum_required(VERSION 3.8)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
include(HunterGate)

HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.19.99.tar.gz"
        SHA1 "55ca271e9276b9973176e3f5a8c0d0dc25e46a53"
)

option(SHAZAM_BUILD_TESTS "build the tests" ON)
set(SHAZAM_CXX_FEATURES_REQUIRED cxx_std_17)
option(SHAZAM_CXX_ALLOW_EXTENSIONS "Whether to allow compiler extensions" ON)

project(Shazam VERSION 0.1 LANGUAGES CXX)

hunter_add_package(Sugar)

if (NOT DEFINED SUGAR_ROOT)
    message(FATAL_ERROR "This cmake project uses Sugar to manage source files. See https://github.com/ruslo/sugar")
else ()
    include(${SUGAR_ROOT}/cmake/Sugar)
    include(sugar_include)
    include(sugar_files)
endif ()


sugar_include(include)
sugar_include(src)

add_library(shazam INTERFACE)
target_include_directories(shazam INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

include(shazam_install_files)
shazam_install_files(DESTINATION include SOURCE include FILES ${ALL_HEADERS})


if (SHAZAM_BUILD_TESTS)
    hunter_add_package(GTest)
    find_package(GTest CONFIG REQUIRED)
    enable_testing()
    sugar_include(tests)
    add_executable(shazam-tests ${TEST_SOURCES} ${ALL_HEADERS})
    target_link_libraries(shazam-tests PRIVATE shazam)
    target_link_libraries(shazam-tests PRIVATE GTest::main)
    target_compile_features(shazam-tests PRIVATE ${SHAZAM_CXX_FEATURES_REQUIRED})
    set_target_properties(shazam-tests PROPERTIES CXX_EXTENSIONS ${SHAZAM_CXX_ALLOW_EXTENSIONS})
endif ()


