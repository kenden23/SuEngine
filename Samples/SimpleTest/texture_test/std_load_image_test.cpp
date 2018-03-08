#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include "GLFW/glfw3.h"

// Include GLM
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "render/GLProgram.h"
#include "sugl/Texture.h"

void GenerateVBO(GLuint &vbo)
{
	if (glIsBuffer(vbo))
	{
		glDeleteBuffers(1, &vbo);
		vbo = 0;
	}
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void ScrollCallBackFunc(GLFWwindow *p, double x, double y)
{

}

int main()
{
	int winWidth = 1024, winHeight = 768;
	char title[] = "deliberate_practice_by_doing";
	GLFWwindow *pwin = glfwCreateWindow(winWidth, winHeight, title, nullptr, nullptr);

	glfwSetInputMode(pwin, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetScrollCallback(pwin, ScrollCallBackFunc);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "can not init glew.");
		getchar();
		return 0;
	}

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);



	return 0;
}