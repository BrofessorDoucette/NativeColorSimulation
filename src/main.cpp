#include <iostream>
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(){


    if(!glfwInit()){

        std::cout << "Failed to init glfw!" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwSetErrorCallback(error_callback);

    GLFWwindow* window;
    window = glfwCreateWindow(1920, 1080, "NativeColorSimulation", NULL, NULL);
    if(!window){


        std::cout << "Failed to open glfw window!" << std::endl;
        exit(EXIT_FAILURE);

    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSetKeyCallback(window, key_callback);
    glfwSwapInterval(1);

    while(!glfwWindowShouldClose(window)){

        glClearColor(255, 0, 0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}