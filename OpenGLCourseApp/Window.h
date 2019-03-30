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
	inline bool* GetKeys() { return keys; };

	GLfloat GetXChange();
	GLfloat GetYChange();

	~Window();

private:
	GLFWwindow* mainWindow;
	GLint width, height;
	GLfloat bufferWidth, bufferHeight;
	bool keys[1024];
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved;

	static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void HandleMouse(GLFWwindow* window, double x, double y);
	void CreateCallback();
};

