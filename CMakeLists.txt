cmake_minimum_required(VERSION 3.10)

project(NativeColorSimulation)

add_subdirectory(external/glfw)

set(SOURCES 
    ./src/main.cpp 
    ./src/Node.cpp 
    ./Include/Node.h)

set(GLAD "./external/glad/include/glad/glad.h"
    "./external/glad/src/glad.c")

add_executable(${PROJECT_NAME} ${SOURCES} ${GLAD})

target_include_directories(${PROJECT_NAME} 
    PRIVATE ./Include
    PUBLIC external/glfw/include
    PUBLIC external/glad/include
    )

target_link_directories(${PROJECT_NAME}
    
    PRIVATE external/glfw/src
    PRIVATE external/glad/src
)

target_link_libraries(${PROJECT_NAME}
    
    glfw
)