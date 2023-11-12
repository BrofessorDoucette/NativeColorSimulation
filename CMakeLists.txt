cmake_minimum_required(VERSION 3.10)

project(NativeColorSimulation)

add_subdirectory(external/glfw)

set(SOURCES 
    ./src/main.cpp 
    ./src/Node.cpp 
    ./Include/Node.h)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} 
    PRIVATE ./Include
    PUBLIC external/glfw/include
    )

target_link_directories(${PROJECT_NAME}
    
    PRIVATE external/glfw/src
)

target_link_libraries(${PROJECT_NAME}
    
    glfw

)