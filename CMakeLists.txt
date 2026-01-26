cmake_minimum_required(VERSION 3.13)
project(MyLegacyPass LANGUAGES CXX)

# ---- C++ config ----
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -Wall")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---- LLVM config ----
find_package(LLVM 10.0 REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# LLVM 10 helpers
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)

# LLVM's include and compile defs
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# add library folder 
add_subdirectory(src)
