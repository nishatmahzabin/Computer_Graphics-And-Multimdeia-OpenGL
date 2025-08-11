#include "glad.h"
#include "glfw3.h"
#include <iostream>

// Function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Vertex shader
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "}\0";

// Fragment shaders for each color
const char *fragmentShaderLime = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.196f, 0.804f, 0.196f, 1.0f);\n" // Lime Green Color
    "}\n\0";

const char *fragmentShaderPurple = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.58f, 0.0f, 0.83f, 1.0f);\n"  // Neon Purple Color
    "}\n\0";

const char *fragmentShaderBlue = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.21f, 0.22f, 0.65f, 1.0f);\n"  // Galaxy Blue Color
    "}\n\0";

unsigned int createShaderProgram(const char* fragSource) {
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Md. Nishat Mahzabin", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Create 3 shader programs
    unsigned int shaderLime = createShaderProgram(fragmentShaderLime);
    unsigned int shaderPurple = createShaderProgram(fragmentShaderPurple);
    unsigned int shaderBlue = createShaderProgram(fragmentShaderBlue);

    // Vertex data for triangles
    float rightTriangle[] = { // 1st quadrant
         0.1f, 0.1f, 0.0f,
         0.6f, 0.1f, 0.0f,
         0.1f, 0.6f, 0.0f
    };

    float equilateralTriangle[] = { // 2nd quadrant
        -0.6f, 0.1f, 0.0f,
        -0.1f, 0.1f, 0.0f,
        -0.35f, 0.54f, 0.0f
    };

    float isoscelesTriangle[] = { // 3rd quadrant
        -0.6f, -0.1f, 0.0f,
        -0.1f, -0.1f, 0.0f,
        -0.35f, -0.5f, 0.0f
    };

    unsigned int VAO[3], VBO[3];
    glGenVertexArrays(3, VAO);
    glGenBuffers(3, VBO);

    float* triangles[] = { rightTriangle, equilateralTriangle, isoscelesTriangle };
    for (int i = 0; i < 3; i++) {
        glBindVertexArray(VAO[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), triangles[i], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderLime);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderPurple);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderBlue);
        glBindVertexArray(VAO[2]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(3, VAO);
    glDeleteBuffers(3, VBO);
    glDeleteProgram(shaderLime);
    glDeleteProgram(shaderPurple);
    glDeleteProgram(shaderBlue);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}