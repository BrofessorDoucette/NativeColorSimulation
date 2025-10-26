cmake_minimum_required(VERSION 3.10)

project(NativeColorSimulation)

add_subdirectory(external/glfw)

set(SOURCES 
    ./src/main.cpp 
    ./src/Node.cpp 
    ./src/Board.cpp
    ./Include/Node.h
    ./Include/Board.h
    ./Include/Shader.h)

set(GLAD "./external/glad/include/glad/glad.h"
    "./external/glad/src/glad.c")

add_executable(${PROJECT_NAME} ${SOURCES} ${GLAD})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED On)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS Off)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/src/Shaders/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/Shaders/)

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