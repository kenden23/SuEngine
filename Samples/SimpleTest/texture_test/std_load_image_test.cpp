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
#include "controllers/Camera.h"

#include "assimp/Importer.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../../SuEngine/stb/stb_image.h"

#include "../utile_test/CameraControlV2.h"

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

	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

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
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

	GLuint vio;
	glGenBuffers(1, &vio);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vio);
	unsigned int indices_data[] = {
		0, 1, 3, 2
	};
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_data), indices_data, GL_STATIC_DRAW);

	// Read our .obj file
	std::vector<unsigned short> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;
	Su::file::readAssimpData("res/suzanne.obj", indices, indexed_vertices, indexed_uvs, indexed_normals);

	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

	GLuint norBuf;
	glGenBuffers(1, &norBuf);
	glBindBuffer(GL_ARRAY_BUFFER, norBuf);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0/*sizeof(float) * 5*/, (void *)0);
	
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		0/*sizeof(float) * 5*/, (void *)(0/*sizeof(float) * 3*/));

	glBindBuffer(GL_ARRAY_BUFFER, norBuf);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	GLProgram glpro;
	glpro.Init();
	glpro.AddShader(GL_VERTEX_SHADER, "shaders/stb_load_image.vs");
	glpro.AddShader(GL_FRAGMENT_SHADER, "shaders/stb_load_image.fs");
	glpro.Finalize();
	glpro.Enable();

	//GLuint tex_buf;
	//glGenTextures(1, &tex_buf);
	//glBindBuffer(GL_TEXTURE_2D, tex_buf);

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

	auto pcam = new Camera(new CameraControlV2);
	pcam->init(pwin);

	glClearColor(0.f, 0.5f, 0.5f, 0.f);
	do 
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		pcam->update(1.f/60.f);

		auto pLoc = glpro.GetUniformLocation("P");
		auto mLoc = glpro.GetUniformLocation("M");
		auto vLoc = glpro.GetUniformLocation("V");

		glm::mat4 p = glm::perspective(glm::radians(45.f), 4.0f / 3.0f, 0.1f, 100.0f);

		glm::mat4 v = glm::lookAt(
			glm::vec3(0, 2, 4),// Camera is here
			glm::vec3(0, 0, 0),// and looks here : at the same position, plus "direction"
			glm::vec3(0, 1, 0)// Head is up (set to 0,-1,0 to look upside-down)
		);

		p = pcam->GetProj();
		v = pcam->GetView();

		glm::mat4 m = glm::mat4(1.f);

		glpro.SetUniformMat4(pLoc, p);
		glpro.SetUniformMat4(mLoc, m);
		glpro.SetUniformMat4(vLoc, v);


		//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		//glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);

		myTex.use();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vio);
		// Draw the triangles !
		glDrawElements(
			GL_TRIANGLES,      // mode
			indices.size(),    // count
			GL_UNSIGNED_SHORT,   // type
			(void*)0           // element array buffer offset
		);

		glfwPollEvents();
		glfwSwapBuffers(pwin);
	} while (!glfwWindowShouldClose(pwin)
		&& GLFW_PRESS != glfwGetKey(pwin, GLFW_KEY_ESCAPE));

	return 0;
}