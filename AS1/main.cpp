#include "Object.hpp"
#include "Window.hpp"

#include "GL/gl_core_3_3.h"
#include "GLFW/glfw3.h"

#include <iostream>

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
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

        //clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        //draw the object
        obj.draw();

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