cmake_minimum_required(VERSION 3.10)
### c++11 standards
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project (fileparser)

# CUDA PACKAGE
find_package(CUDA REQUIRED)
set(CUDA_SEPARABLE_COMPILATION ON)
set(CUDA_PROPAGATE_HOST_FLAGS OFF)
set(CUDA_HOST_COMPILER g++)

# COMPILE CU FILES
file(GLOB CUDA_FILES "Source/" *.cu)
list( APPEND CUDA_NVCC_FLAGS${CUDA_NVCC_FLAGS};-gencode arch=compute_30,code=sm_30; -std=c++11)
CUDA_COMPILE(CU_O ${CUDA_FILES})

#Specify cuda files
cuda_add_executable(fileparser Source/FileParser.cu)

# Specify binary name and source file to build it from
add_executable(fileparsercpp Source/FileParser.cpp)
add_executable(fileparserarrays Source/FileParserUsingArrays.cpp)

