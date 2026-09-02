cmake_minimum_required(VERSION 3.23)

project(game)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(COPY assets/
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_subdirectory(App)
add_subdirectory(Core)

target_include_directories(App
    PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
)

target_link_libraries(App
    PRIVATE
        ${SDL2_LIBRARIES}
        SDL2_image
)