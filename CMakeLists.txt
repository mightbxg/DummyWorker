cmake_minimum_required(VERSION 3.10)

project(DummyWorker)

find_package(Threads REQUIRED)

add_executable(dummy_worker main.cpp)
target_link_libraries(dummy_worker Threads::Threads)
target_compile_features(dummy_worker PRIVATE cxx_std_17)