project(FManager)

include_directories("libs/FServer2.0/FServer2_0/source/Client")
include_directories("libs/FServer2.0/FServer2_0/source/Server")
include_directories("libs/FServer2.0/FServer2_0/libs/asio-1.24.0/include")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(app main.cpp)

target_compile_features(app PRIVATE cxx_std_17)

add_subdirectory(libs/FServer2.0/FServer2_0)

target_link_libraries(app PRIVATE libFS)

set(CMAKE_CXX_FLAGS "-pthread")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)