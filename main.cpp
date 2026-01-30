#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "truck.h"

glm::vec3 translation(0.0f, 0.0f, 0.0f);
float rotationAngle = 0.0f;
float scaleFactor = 0.5f;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        translation.y += 0.01f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        translation.y -= 0.01f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        translation.x -= 0.01f;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        translation.x += 0.01f;

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        rotationAngle += glm::radians(1.0f);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        rotationAngle -= glm::radians(1.0f);

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        scaleFactor *= 1.01f;
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        scaleFactor /= 1.01f;

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        translation = glm::vec3(0.0f);
        rotationAngle = 0.0f;
        scaleFactor = 0.5f;
    }
}

int main()
{
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "CringeTruck2 BRAT edition", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
        return -1;

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe

    unsigned int shaderProgram = createShaderProgram();
    loadTruckModel("cringetruck2.obj");
    setupTruckBuffers();

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.0f, 1.0f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 transform = glm::mat4(1.0f);
        // transform = glm::translate(transform, translation);
        transform = glm::translate(transform, translation + glm::vec3(0.0f, 0.0f, 0.0f));
        transform = glm::rotate(transform, rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
        transform = glm::scale(transform, glm::vec3(scaleFactor));

        // glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.3f, -2.5f));
        glm::mat4 view = glm::lookAt(
            glm::vec3(4.0f, 0.0f, 0.0f), // camera position
            glm::vec3(0.0f, 0.0f, 0.0f), // origin
            glm::vec3(0.0f, 1.0f, 0.0f)  // up direction
        );
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.f / 600.f, 0.1f, 100.f);

        glUseProgram(shaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(transform));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        drawTruck();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cleanupTruckBuffers();
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}