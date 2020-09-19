cmake_minimum_required(VERSION 3.0)

project(TracingPoint)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(CURL REQUIRED)

include_directories (
    hsGeneticAlgorithm
    curl-7.72.0/include
    )

set(SOURCE 
    ./main.cpp
    ./hsGeneticAlgorithm/functions.cpp
    ./hsGeneticAlgorithm/de.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCE})