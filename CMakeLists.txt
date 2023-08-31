cmake_minimum_required(VERSION 3.16)
project(libtmt C CXX)

# Thanks to https://google.github.io/googletest/quickstart-cmake.html for help setting up Googletest.

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20) # Technically C++20 is needed for designated initializers. Clang supports them with C++17.

include_directories(.)

add_library(tmt
        tmt.c
        tmt.h)

option(UT_MEM_LEAK_CHECK "Run the memory leak checker on windows unit tests (no effect on non-Windows)" ON)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG        release-1.12.1
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_executable(
            tmt_test

            test/main.cpp

            test/infra/basic_scene.cpp
            test/infra/GMockCallbacks.cpp
            test/infra/TestVtWrapper.cpp
            test/infra/VtStdCallbacks.cpp
            test/infra/win_mem_leak.cpp
            test/infra/write_strings.cpp

            test/tests/basic_writing.cpp
            test/tests/create_and_destroy.cpp
            test/tests/csi_params.cpp
            test/tests/cursor.cpp
            test/tests/default_vals.cpp
            test/tests/scrolling.cpp

            test/tests/capabilities/bel.cpp
            test/tests/capabilities/cbt.cpp
            test/tests/capabilities/cup.cpp
            test/tests/capabilities/cux_and_kbs.cpp
            test/tests/capabilities/ech.cpp
            test/tests/capabilities/ed.cpp
            test/tests/capabilities/home.cpp
            test/tests/capabilities/ht.cpp
            test/tests/capabilities/indn.cpp
            test/tests/capabilities/rin.cpp
            test/tests/capabilities/sgr.cpp
            test/tests/capabilities/u7.cpp
            test/tests/capabilities/u8_and_u9.cpp
            )

    target_link_libraries(
            tmt_test
            tmt
            GTest::gtest_main
            gmock
    )

    if (WIN32 AND UT_MEM_LEAK_CHECK)
            add_compile_definitions(tmt_test UT_MEM_LEAK_CHECK)
    endif()

    include(GoogleTest)
    gtest_discover_tests(tmt_test)
endif()
