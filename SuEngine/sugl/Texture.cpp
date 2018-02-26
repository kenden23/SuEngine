#include "Texture.h"

Texture2D::Texture2D(const std::string & fileName)
{
	auto iinfo = loadPicToMem(fileName);

	glGenTextures(1, &m_textureObject);
	glBindTexture(GL_TEXTURE_2D, m_textureObject);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iinfo.width, iinfo.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, iinfo.data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture2D::use(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, m_textureObject);
}

Texture2D::ImageInfo Texture2D::loadPicToMem(const std::string & fileName)
{

}

void Texture2D::loadMenToGL(const GLvoid * data)
{

}
