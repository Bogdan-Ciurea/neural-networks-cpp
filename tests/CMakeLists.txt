FetchContent_Declare(
    googletest
    GIT_REPOSITORY git@github.com:google/googletest.git
    GIT_TAG release-1.12.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

# add header files from the google test library
include_directories(${gtest_SOURCE_DIR}/googletest/include ${gtest_SOURCE_DIR})

SET(TEST_NAME test-${PROJECT_NAME})

SET(TEST_SOURCES 
    math-tests.cpp
    image-tests.cpp
)

# Add the test executable
add_executable(
    ${TEST_NAME}
    ${TEST_SOURCES}
)

target_compile_features(${TEST_NAME} PRIVATE cxx_std_14)

target_link_libraries(${TEST_NAME} PRIVATE neural-library gtest_main)
set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "..")

gtest_discover_tests(${TEST_NAME})

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})