cmake_minimum_required(VERSION 3.0)
project(test_coer C)

set (test_coer_VERSION_MAJOR 0)
set (test_coer_VERSION_MINOR 0)
set (test_coer_VERSION_PATCH 1)

file(GLOB sources src/*.c)

add_executable(test_coer  ${sources})

add_library(coer STATIC ${sources})

# same here
# target_include_directories (test_coer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs)
# target_include_directories (test_coer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../../contrib/include)
target_include_directories (test_coer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../../contrib/deps)

# find_library(GPC_LIBRARY gpc HINTS ${CMAKE_CURRENT_SOURCE_DIR}/../../../contrib/platform/linux2/x86_64)

target_link_libraries(test_coer LINK_PUBLIC coer m)
