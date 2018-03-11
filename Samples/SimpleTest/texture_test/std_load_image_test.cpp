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

#define STB_IMAGE_IMPLEMENTATION
#include "../../../SuEngine/stb/stb_image.h"

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

void ResizeCB(GLFWwindow *p, int w, int h)
{
	glViewport(0, 0, w, h);
}

int main()
{
	glfwInit();

	int winWidth = 1024, winHeight = 768;
	char title[] = "deliberate_practice_by_doing";
	GLFWwindow *pwin = glfwCreateWindow(winWidth, winHeight, title, nullptr, nullptr);
	glfwMakeContextCurrent(pwin);

	glfwSetInputMode(pwin, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetScrollCallback(pwin, ScrollCallBackFunc);
	glfwSetFramebufferSizeCallback(pwin, ResizeCB);

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

	float vertex_data[] = {
		-0.5f, -0.5f, 0.f, 0.f, 1.f,
		0.5f, -0.5f, 0.f, 1.f, 1.f,
		0.5f, 0.5f, 0.f, 1.f, 0.f,
		-0.5f, 0.5f, 0.f, 0.f, 0.f,
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

	GLuint vio;
	glGenBuffers(1, &vio);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vio);
	unsigned int indices_data[] = {
		0, 1, 3, 2
	};
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_data), indices_data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		sizeof(float) * 5, (void *)(sizeof(float) * 3));

	GLProgram glpro;
	glpro.Init();
	glpro.AddShader(GL_VERTEX_SHADER, "shaders/stb_load_image.vs");
	glpro.AddShader(GL_FRAGMENT_SHADER, "shaders/stb_load_image.fs");
	glpro.Finalize();
	glpro.Enable();

	GLuint tex_buf;
	glGenTextures(1, &tex_buf);
	glBindBuffer(GL_TEXTURE_2D, tex_buf);

	Texture2D myTex("res/im.bmp");
	myTex.use();

	//int width, height, nrChannels;
	//unsigned char *data = stbi_load("D:/Data ×ÊÁÏ/pretty/1.jpg", &width, &height, &nrChannels, 0);
	//unsigned char *data = stbi_load("res/im.bmp", &width, &height, &nrChannels, 4);
	//Su::SimpleImageInfo sif;
	//Su::file::readImage_BMP(sif, "res/im.bmp");
	//width = sif.width;
	//height = sif.height;
	//void *data = sif.data;


	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, /GL_UNSIGNED_BYTE,/ data);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glClearColor(0.f, 0.5f, 0.5f, 0.f);
	do 
	{
		glClear(GL_COLOR_BUFFER_BIT);

		//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);

		glfwPollEvents();
		glfwSwapBuffers(pwin);
	} while (!glfwWindowShouldClose(pwin)
		&& GLFW_PRESS != glfwGetKey(pwin, GLFW_KEY_ESCAPE));

	return 0;
}