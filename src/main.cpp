#include <iostream>
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

int main(){


    int vWidth = 1920;
    int vHeight = 1080;

    if(!glfwInit()){

        std::cout << "Failed to init glfw!" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwSetErrorCallback(error_callback);

    GLFWwindow* window;
    window = glfwCreateWindow(vWidth, vHeight, "NativeColorSimulation", NULL, NULL);
    if(!window){


        std::cout << "Failed to open glfw window!" << std::endl;
        exit(EXIT_FAILURE);

    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    gladLoadGL();

    glViewport(0, 0, vWidth, vHeight);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    float positions[6] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    while(!glfwWindowShouldClose(window)){

        processInput(window);

        glClearColor(0, 0, 0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}