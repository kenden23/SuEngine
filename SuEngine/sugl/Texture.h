#pragma once

#include <string>

#include "GL/glew.h"

class Texture2D
{
public:
	Texture2D(const std::string &fileName);
	void use(GLenum textureUnit);
protected:
	struct ImageInfo
	{
		int width, height;
		GLvoid *data;
	};
	ImageInfo loadPicToMem(const std::string &fileName);
	void loadMenToGL(const GLvoid *data);

	GLuint m_textureObject;
};