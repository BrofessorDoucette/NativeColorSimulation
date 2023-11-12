#include <iostream>
#include <GLFW/glfw3.h>

int main(){

    GLFWwindow* window;
    if(!glfwInit()){

        std::cout << "Failed to init glfw!" << std::endl;
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(300, 300, "NativeColorSimulation", NULL, NULL);
    if(!window){


        std::cout << "Failed to open glfw window!" << std::endl;
        exit(EXIT_FAILURE);

    }

    while(!glfwWindowShouldClose(window)){

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}