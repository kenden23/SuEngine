#pragma once

#include "GLFW/glfw3.h"

#include "../SuEngine.h"

namespace Su
{

struct SU_API VertexArray
{
	VertexArray();
	~VertexArray();

	void genVao();

	GLuint vao;
	GLuint vbo;

};

}

class SU_API SuGlFunc
{
	SuGlFunc();
	~SuGlFunc();
public:
	static SuGlFunc *getInstance();

	void initGlew();

protected:
private:
};