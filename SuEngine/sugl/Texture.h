#pragma once

#include <string>

#include "GL/glew.h"

#include "../file/SuFile.h"

class SU_API Texture2D
{
public:
	
	Texture2D(const std::string &fileName);
	~Texture2D();
	void use(GLenum textureUnit);
protected:

	void loadPicToMem(Su::SimpleImageInfo &outInfo, const std::string &fileName);
	void loadMenToGL(Su::SimpleImageInfo &inInfo);

	GLuint m_textureObject;
};