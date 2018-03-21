#pragma once

#include <string>

#include "GL/glew.h"

#include "../file/SuFile.h"

class SU_API Texture2D
{
public:
	
	Texture2D(const std::string &fileName);
	~Texture2D();
	void use(GLenum textureUnit = GL_TEXTURE0);
protected:

	void loadPicToGL(const std::string &fileName);

	GLuint m_textureObject;
};