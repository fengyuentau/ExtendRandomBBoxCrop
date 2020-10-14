cmake_minimum_required(VERSION 3.5)
project(DALI_plugin)
find_package(CUDA 10.0 REQUIRED)

execute_process(
        COMMAND python -c "import nvidia.dali as dali; print(dali.sysconfig.get_lib_dir())"
        OUTPUT_VARIABLE DALI_LIB_DIR)
string(STRIP ${DALI_LIB_DIR} DALI_LIB_DIR)

execute_process(
        COMMAND python -c "import nvidia.dali as dali; print(\" \".join(dali.sysconfig.get_compile_flags()))"
        OUTPUT_VARIABLE DALI_COMPILE_FLAGS)
string(STRIP ${DALI_COMPILE_FLAGS} DALI_COMPILE_FLAGS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 ${DALI_COMPILE_FLAGS} ")
set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -std=c++14 ${DALI_COMPILE_FLAGS} ")
link_directories( "${DALI_LIB_DIR}" )

cuda_add_library(ExtendRandomBBoxCrop SHARED extend_bbox_crop.cc)
target_link_libraries(ExtendRandomBBoxCrop dali)