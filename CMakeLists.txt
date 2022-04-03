cmake_minimum_required(VERSION 3.16.5)
project(cmob)
set(glog_DIR "D:\\vcpkg\\vcpkg\\packages\\glog_x64-mingw-static\\share\\glog")
set(gflags_DIR "D:\\vcpkg\\vcpkg\\packages\\gflags_x64-mingw-static\\share\\gflags")
set(nlohmann_json_DIR "D:\\vcpkg\\vcpkg\\packages/nlohmann-json_x64-mingw-static/share/nlohmann_json/")
#set(glog_DIR "D:\\vcpkg\\vcpkg\\packages\\glog_x64-mingw-static\\share\\glog")
#set(gflags_DIR "D:\\vcpkg\\vcpkg\\packages\\gflags_x64-mingw-static\\share")
set(CMAKE_CXX_STANDARD 17)
find_package(glog CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)


add_executable(cmob main.cpp)
target_link_libraries(cmob
        PRIVATE nlohmann_json::nlohmann_json
        PRIVATE glog::glog
        )
