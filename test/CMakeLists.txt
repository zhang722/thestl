include_directories(${PROJECT_SOURCE_DIR}/src)
set(TEST_SRC test.cpp)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
add_executable(stltest ${TEST_SRC})