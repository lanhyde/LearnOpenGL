#pragma once

#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialize();

	inline GLfloat GetBufferWidth() { return bufferWidth; }
	inline GLfloat GetBufferHeight() { return bufferHeight; }
	inline bool ShouldClose() { return glfwWindowShouldClose(mainWindow); }
	inline void SwapBuffers() { return glfwSwapBuffers(mainWindow); }

	~Window();

private:
	GLFWwindow* mainWindow;
	GLint width, height;
	GLfloat bufferWidth, bufferHeight;

};

