#include "SuGlFunc.h"

#include <stdio.h>
#include <stdlib.h>

namespace Su
{

VertexArray::VertexArray() :vao(0)
, vbo(0)
{
	genVao();
}

VertexArray::~VertexArray()
{
	if (glIsBuffer(vbo))
	{
		glDeleteBuffers(1, &vbo);
		vbo = 0;
	}

	if (glIsVertexArray(vao))
	{
		glDeleteVertexArrays(1, &vao);
		vao = 0;
	}	
}

void VertexArray::genVao()
{
	if (glIsVertexArray(vao))
	{
		glDeleteVertexArrays(1, &vao);
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

}

SuGlFunc::SuGlFunc()
{

}

SuGlFunc::~SuGlFunc()
{

}

SuGlFunc * SuGlFunc::getInstance()
{
	static SuGlFunc inst;
	return &inst;
}

void SuGlFunc::initGlew()
{
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		exit(-1);
	}
}

