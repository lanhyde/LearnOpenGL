// OpenGLCourseApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"

using namespace std;

const GLint WIDTH = 800, HEIGHT = 600;

Window mainWindow;
Camera camera;
vector<Mesh*> meshList;
vector<Shader> shaderList;

// Vertex Shader
static const char* vShader = "Shaders/shader.vert";
// Fragment shader
static const char* fShader = "Shaders/shader.frag";

void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	Mesh* mesh = new Mesh();
	mesh->CreateMesh(vertices, indices, sizeof(indices) / sizeof(*indices), sizeof(vertices) / sizeof(*vertices));
	meshList.push_back(mesh);	
	
	Mesh* mesh2 = new Mesh();
	mesh2->CreateMesh(vertices, indices, sizeof(indices) / sizeof(*indices), sizeof(vertices) / sizeof(*vertices));
	meshList.push_back(mesh2);
}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main()
{
	mainWindow = Window(WIDTH, HEIGHT);
	mainWindow.Initialize();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 0.01f, 1.0f);
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;
	glm::mat4 projection = glm::perspective(45.0f, mainWindow.GetBufferWidth() / mainWindow.GetBufferHeight(), 0.1f, 100.0f);

	// Loop until window closed
	while (!mainWindow.ShouldClose())
	{
		// Get + Handle user input events
		glfwPollEvents();
		camera.KeyControl(mainWindow.GetKeys());
		// Clear window
		glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		glm::mat4 model(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		//model = glm::rotate(model, currAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();


		glUseProgram(0);

		mainWindow.SwapBuffers();
	}

	return 0;
}