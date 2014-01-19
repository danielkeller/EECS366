#include "GL/gl_core_3_3.h"
#include "GLFW/glfw3.h"

#include "Shader.hpp"
#include "Object.hpp"

#include <iostream>

void CheckGLError()
{
	GLenum err = glGetError();
	while (err != GL_NO_ERROR) {
		std::cerr << "Gl error [" << err << "] " << (err) << std::endl; //gluErrorString
		err = glGetError();
	}
}

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
	getchar();
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) 
        exit(EXIT_FAILURE);
	
	//only allow non-deprecated GL3.3 calls
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
	//glfwSwapInterval(1); //set vsync
    glfwSetKeyCallback(window, key_callback);
	/*
	glewExperimental = GL_TRUE; //needed for core profile to load correctly
	GLenum err = glewInit();
	glGetError(); //clear bogus GL error
	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(EXIT_FAILURE);
	}*/
	if(ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		std::cerr << "Error in glLoadGen\n";
		glfwDestroyWindow(window);
		glfwTerminate();
        exit(EXIT_FAILURE);
	}

	ShaderProgram prgm("simple.vert", "simple.frag");
	Object obj;
    
	while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
		glViewport(0, 0, (GLsizei) width, (GLsizei) height);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		prgm.use();
		obj.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}