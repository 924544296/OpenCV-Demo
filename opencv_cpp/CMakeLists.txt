# CMakeList.txt : CMake project for opencv_cpp, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("opencv_cpp")

# opencv
#set(OpenCV_DIR "D:/software/opencv/opencv490/build")
#find_package(OpenCV REQUIRED)
#include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("D:/software/opencv/opencv490/build/include"
                    "D:/software/opencv/opencv490/build/include/opencv2")
link_directories("D:/software/opencv/opencv490/build/x64/vc16/lib")
# eigen 
#set(Eigen3_DIR "D:/software/eigen/cmake")
#find_package(Eigen3 REQUIRED)
#include_directories(${EIGEN3_INCLUDE_DIRS})
#include_directories("D:/software/eigen/eigen-3.4.0/Eigen")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")


# Add source to this project's executable.
add_executable (opencv_cpp "functions.h" "functions.cpp" "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET opencv_cpp PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
# opencv
#target_link_libraries(DeepLearning ${OpenCV_LIBS})
target_link_libraries(opencv_cpp opencv_world490d)