cmake_minimum_required(VERSION 3.26)

project(SNN-MNIST)

set(CMAKE_CXX_STANDARD 20)

add_executable(
    ${PROJECT_NAME}
    source/layer.cpp
    source/main.cpp
    source/neuralnetwork.cpp
    source/parser.cpp
    source/window.cpp
    source/text.cpp
    source/numberdisplay.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/headers)

# include and link SDL2
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/SDL2/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/SDL2/lib)
target_link_libraries(${PROJECT_NAME} mingw32 SDL2main SDL2 SDL2_ttf)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})