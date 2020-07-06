#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// ���������
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: ������������� � ����������������
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw �������� ����
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL for Ravesli.com!", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // glad: �������� ���� ���������� �� OpenGL-�������
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ���������������� ����������� ��������� OpenGL
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // �������������� ����� ��������� ���������
    // -------------------------
    Shader shader("../9.1.geometry_shader.vs", "../9.1.geometry_shader.fs", "../9.1.geometry_shader.gs");

    // ��������� ��������� ������ (�������(-��)) � ��������� ��������� ���������
    // ------------------------------------------------------------------
    float points[] = {
        -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // �������-�����
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // �������-������
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // ������-������
        -0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // ������-�����
    };
    unsigned int VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindVertexArray(0);

    // ���� ����������
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // ���������
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ��������� �����
        shader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, 4);

        // glfw: ����� ���������� ��������� � ������� �������. ����� ������� �����\������� (���� �� ������/�������� ������, ��������� ������ ���� � �.�.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // �����������: ������������ ������, ���������� ��� �������:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

// glfw: ������ ���, ����� ���������� ������� ���� (������������� ��� ����. ��������), ���������� ������ �������
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // ����������, ��� ������� ������������� ����� �������� ����; �������� ��������,
    // ��� ������ � ������ ����� ����������� ������, ��� ������� �� retina -��������.
    glViewport(0, 0, width, height);
}

