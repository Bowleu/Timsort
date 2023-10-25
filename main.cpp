#include <iostream>
#include <chrono>
#include "ts.h"
#include "graphicsFunctions.h"

using namespace std;
using namespace chrono;

const char* loadFile(const char* fileName) {
    FILE* shader;
    char* chars = new char[8000];
    memset(chars, 0, 8000);
    fopen_s(&shader, fileName, "rb");
    fread(chars, sizeof(char), 8000, shader);
    fclose(shader);
    return chars;
}

const char* vertex_shader = loadFile("Shaders/vertex.glsl");
const char* fragment_shader = loadFile("Shaders/fragment.glsl");
int windowSizeY = 1080;
int windowSizeX = 1920;

GLint shiftupLocation, shiftLocation, indexLocation;

GLFWwindow* window;

int main()
{
    srand(time(0));
    setlocale(0, "");
    int n;
    vector <int> arr;
    vector <int> arrCopy;

    cout << "При вводе до 1024 элементов включительно откроется графическая визуализация сортировки!\n\n";
    cout << "Введите число элементов: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        arr.push(rand() % (n * 2) - n);
        cout << arr[i] << ' ';
    }
    arrCopy = arr;
    cout << '\n';

    auto start = high_resolution_clock::now();
    arr = timsort(arr);
    auto end = high_resolution_clock::now();
    auto est = duration_cast<microseconds>(end - start);
    cout << '\n';
    for (int i = 0; i < n; i++) {
        cout << arr[i] << ' ';
    }
    cout << "\nEstimated time: " << est.count() << " microseconds.\n";

    /* When n > 1024 visualisation won't start */
    if (n > 1024)
        return 2;

    if (!glfwInit())
    {
        cout << "GLFW initialisation failed!\n";
        return -1;
    }


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    window = glfwCreateWindow(1280, 720, "Timsort visualisation", NULL, NULL);
    int screenWidth, screenHeight;

    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    _init_();
    glViewport(0, 0, screenWidth, screenHeight);
    cout << "\n\nOpenGL version: " << glGetString(GL_VERSION) << "\n\n";

    /* Setting callbacks */
    glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
    glfwSetKeyCallback(window, glfwKeyCallback);
    glClearColor(0, 0, 0, 1);

    GLuint sp = createShaderProgram();

    GLfloat points[12] = {-0.95f, -1.0f, 0.0f,
                          -0.9499f, -1.0f, 0.0f,
                          -0.9499f, -0.8f, 0.0f,
                          -0.95f, -0.8f, 0.0f };

    /* Uniform locations */
    shiftLocation = glGetUniformLocation(sp, "shift");
    shiftupLocation = glGetUniformLocation(sp, "shiftup");
    indexLocation = glGetUniformLocation(sp, "index");

    GLuint pointsVBO = 0;
    glGenBuffers(1, &pointsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

    glUseProgram(sp);

    arrCopy = timsortShow(arrCopy);

    drawArr(arrCopy, arrCopy[n - 1], arrCopy[0]);

    while (!glfwWindowShouldClose(window))    
    {
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}