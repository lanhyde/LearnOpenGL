#include "pch.h"
#include "Window.h"

using namespace std;

Window::Window()
{
	width = 800;
	height = 600;
	for(size_t i = 0; i < 1024; ++i)
	{
		keys[i] = false;
	}
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
}

int Window::Initialize()
{
	// Initialize GLFW
	if (!glfwInit())
	{
		cerr << "GLFW initialization failed!" << endl;
		glfwTerminate();
		return 1;
	}
	// Setup GLFW window properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core profile = No backwards compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		cerr << "GLFW window creation failed!" << endl;
		glfwTerminate();
		return 1;
	}
	// Get Buffer size information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);
	// handle input event
	CreateCallback();
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Allow modern extension features
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cerr << "GLEW initialization failed!" << endl;
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);
	// Setup Viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::CreateCallback()
{
	glfwSetKeyCallback(mainWindow, HandleKeys);
	glfwSetCursorPosCallback(mainWindow, HandleMouse);
}

void Window::HandleMouse(GLFWwindow* window, double x, double y)
{
	auto theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if(theWindow->mouseFirstMoved)
	{
		theWindow->lastX = x;
		theWindow->lastY = y;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = x - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - y;

	theWindow->lastX = x;
	theWindow->lastY = y;

	cout << "x: " << theWindow->xChange << ", y: " << theWindow->yChange << endl;
}



void Window::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	auto theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if(key >= 0 && key < 1024)
	{
		if(action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			cout << "Pressed : " << key << endl;
		}
		else if(action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			cout << "Released: " << key << endl;
		}
	}
}

GLfloat Window::GetXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::GetYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}




Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}
