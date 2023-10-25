#pragma once
#include <glad.h>
#include <glfw3.h>

using namespace std;
using namespace chrono;

void _init_() {
    gladLoadGL();
}

extern int windowSizeX, windowSizeY;
extern const char *vertex_shader, *fragment_shader;
extern GLint shiftLocation, shiftupLocation, indexLocation;
extern GLFWwindow* window;

void glfwWindowSizeCallback(GLFWwindow* window, int width, int height) {
    windowSizeX = width;
    windowSizeY = height;
    glViewport(0, 0, windowSizeX, windowSizeY);
}

void glfwKeyCallback(GLFWwindow* window, int key, int scanCode, int action, int node) {
    if (key == GLFW_KEY_ESCAPE and action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

GLuint createShaderProgram() {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader, nullptr);
    glShaderSource(fragmentShader, 1, &fragment_shader, nullptr);

    int success;
    GLchar inf[500];

    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        cout << "Vertex shader problem!\n";
        glGetShaderInfoLog(vertexShader, 500, NULL, inf);
        for (int i = 0; i < 500; i++)
            cout << inf[i];
        cout << '\n';
    }

    glCompileShader(fragmentShader);
    success = 1;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        cout << "Fragment shader problem!\n";
        glGetShaderInfoLog(fragmentShader, 500, NULL, inf);
        for (int i = 0; i < 500; i++)
            cout << inf[i];
        cout << '\n';
    }

    GLuint sp = glCreateProgram();
    glAttachShader(sp, vertexShader);
    glAttachShader(sp, fragmentShader);
    glLinkProgram(sp);

    success = 1;
    glGetProgramiv(sp, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(sp, 500, NULL, &inf[0]);
        cout << "Bad linkin'!\n";
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return sp;
}


void drawArr(vector <int> arr, int mx, int mn) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    int n = arr.getLength();
    for (int i = 0; i < n; i++) {
        float shiftup = ((0.7 - (-0.8)) / ((float)mx - (float)mn)) * (float)(arr[i] - mn);
        float shift = (0.95 - (-0.95)) / (float)n;
        glUniform1f(shiftLocation, shift);
        glUniform1f(shiftupLocation, shiftup);
        glUniform1f(indexLocation, i);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
    glfwSwapBuffers(window);
    if (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }
    else {
        glfwTerminate();
        exit(0);
    }
}