cmake_minimum_required(VERSION 3.14)
project(ir-rpy-stat)

set(CMAKE_CXX_STANDARD 17)

if(NOT WIN32)
    option(COVERAGE "Enable coverage reporting" ON)
else()
    option(COVERAGE "Enable coverage reporting" OFF)
endif()

if(COVERAGE)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        message(STATUS "Building with code coverage enabled.")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -g")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    else()
        message(FATAL_ERROR "Coverage only supported with GCC or Clang")
    endif()
endif()

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

include_directories(
    ${RDKAFKA_INCLUDE_DIRS}
    
    ${CMAKE_SOURCE_DIR}/src

    ${CMAKE_SOURCE_DIR}/tests
)

add_executable(
    test-ir-rpy-stat.tsk

    tests/hello.t.cpp
    tests/metadata-out.output-format-metadata.t.cpp
    tests/options-parser.find-files-to-process.t.cpp
    tests/options-parser.load-options.t.cpp

    src/metadata-out.cpp
    src/options-parser.cpp
    src/rpy-metadata.cpp
)

add_executable(
    ir-rpy-stat.tsk
     
    src/main.cpp

    src/metadata-out.cpp
    src/options-parser.cpp
    src/rpy-metadata.cpp
)

target_link_libraries(ir-rpy-stat.tsk 
    PRIVATE
)

target_link_libraries(
    test-ir-rpy-stat.tsk
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(test-ir-rpy-stat.tsk
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# Coverage report target
if(COVERAGE)
    find_program(LCOV_PATH lcov)
    find_program(GENHTML_PATH genhtml)

    if(LCOV_PATH AND GENHTML_PATH)
        add_custom_target(coverage
            COMMAND ${LCOV_PATH} --capture --directory . --output-file coverage.info --rc lcov_branch_coverage=1 --ignore-errors mismatch
            COMMAND ${LCOV_PATH} --remove coverage.info '/usr/*' --output-file coverage.info --rc lcov_branch_coverage=1
            COMMAND ${LCOV_PATH} --list coverage.info
            COMMAND ${GENHTML_PATH} coverage.info --output-directory coverage-report
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Generating coverage report..."
            COMMAND ${LCOV_PATH} --zerocounters --directory . --rc lcov_branch_coverage=1
        )
    else()
        message(WARNING "lcov/genhtml not found! Coverage target will not be available.")
    endif()
endif()

