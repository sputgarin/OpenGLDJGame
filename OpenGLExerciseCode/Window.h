#pragma once

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

using namespace std;

class Window
{
	// We made these method static to make them compatible
	// With the GLFW Callbacks (because they don't support this->)
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	static void error_callback(int error, const char* msg) {
		cerr << " [" << error << "] " << msg << endl;
	}
	GLFWwindow* window;

public:
	// we introduced a bool to show whether creating the window
	// was successful or not
	bool success{};
	Window(int width, int height) { // Start (Awake)
		glfwSetErrorCallback(error_callback);

		// Initialize GLFW
		if (!glfwInit()) { // Exit, if it failed
			cout << "Failed to init GLFW" << endl;
			return; // We don't return -1 anymore, instead we leave success at false
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		// Request Window from Operating System
		// And assign it to public class variable, so it can 
		// be accessed from the outside
		window = glfwCreateWindow(800, 600,
			"LearnOpenGL", nullptr, nullptr);

		if (window == nullptr)
		{
			cout << "Failed to create GLFW window" << endl;
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(window);

		// Initialize GLAD (connects OpenGL Functions)
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			cout << "Failed to initialize GLAD" << endl;
			glfwTerminate();
			return;
		}
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		// Initialization ends here
		success = true; // We set success to be true
	}

	bool shouldClose() {
		return glfwWindowShouldClose(this->window);
	}

	void present() {
		glfwSwapBuffers(window);
	}

	void processInput()
	{
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}
};

