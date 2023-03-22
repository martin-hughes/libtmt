cmake_minimum_required(VERSION 3.22)
project(libtmt C CXX)

# Thanks to https://google.github.io/googletest/quickstart-cmake.html for help setting up Googletest.

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_library(tmt
        tmt.c
        tmt.h)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG        release-1.11.0
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_executable(
            tmt_test
            test/callback_handler.cpp
            test/main.cpp
            test/TestVtWrapper.cpp
            test/win_mem_leak.cpp
            test/write_strings.cpp

            test/tests/basic_writing.cpp
            test/tests/create_and_destroy.cpp
            test/tests/csi_params.cpp
            test/tests/cursor.cpp
            test/tests/default_vals.cpp
            test/tests/ech.cpp
    )

    target_link_libraries(
            tmt_test
            tmt
            GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(tmt_test)
endif()
