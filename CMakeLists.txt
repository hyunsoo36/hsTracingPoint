cmake_minimum_required(VERSION 3.0)

project(TracingPoint)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(CURL_LIBRARY "-lcurl") 
find_package(CURL REQUIRED)

include_directories (
    ${CURL_INCLUDE_DIR}
    hsGeneticAlgorithm
    )

set(SOURCE 
    ./main.cpp
    ./hsGeneticAlgorithm/functions.cpp
    ./hsGeneticAlgorithm/de.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})