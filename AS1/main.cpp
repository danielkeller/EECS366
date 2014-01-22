#include "stdafx.h"
#include "Object.hpp"
#include "Window.hpp"

#include "GLFW/glfw3.h"

#include <iostream>

bool perspective = true;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
        return;
    switch (key)
    {
    case GLFW_KEY_Q:
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, GL_TRUE);
        break;
    case GLFW_KEY_P:
        perspective = !perspective;
        break;
    }
}

int main(void)
try
{
    //create the basic window
    Window w;
    //add our keyboard input callback
    glfwSetKeyCallback(w.window, key_callback);

    //load the object
    Object obj("teapot.obj");

    //clear to black
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    //our main loop
    while (!glfwWindowShouldClose(w.window))
    {
        //set the GL draw surface to the same size as the window
        int width, height;
        glfwGetFramebufferSize(w.window, &width, &height);
        glViewport(0, 0, (GLsizei) width, (GLsizei) height);

        //set the perspective matrix
        glm::mat4 perspMat;
        if (perspective)
            perspMat = glm::perspective(glm::half_pi<float>(), (float)width / height, .01f, 100.f);
        else
            perspMat = glm::ortho(-1.f, 1.f, -1.f, 1.f);

        glm::mat4 view = glm::translate(glm::vec3(0.f, 0.f, -4.f));

        //clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        //draw the object
        obj.draw(perspMat * view);

        //swap draw buffer and visible buffer
        glfwSwapBuffers(w.window);
        glfwPollEvents();
    }
    
    return EXIT_SUCCESS;
}
catch (const char* mesg)
{
    std::cerr << mesg << "\nPress enter to exit...\n";
    getchar();
    return EXIT_FAILURE;
}