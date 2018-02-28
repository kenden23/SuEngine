#include "Texture.h"

Texture2D::Texture2D(const std::string & fileName)
{
	Su::SimpleImageInfo iinfo;
	loadPicToMem(iinfo, fileName);
	loadMenToGL(iinfo);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_textureObject);
}

void Texture2D::use(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, m_textureObject);
}

void Texture2D::loadPicToMem(Su::SimpleImageInfo &outInfo, const std::string & fileName)
{
	Su::file::readImage_BMP(outInfo, fileName.data());
}

void Texture2D::loadMenToGL(Su::SimpleImageInfo &inInfo)
{
	glGenTextures(1, &m_textureObject);
	glBindTexture(GL_TEXTURE_2D, m_textureObject);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, inInfo.width, inInfo.height, 0, GL_RGB, GL_UNSIGNED_BYTE, inInfo.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glGenerateMipmap(GL_TEXTURE_2D);
}
