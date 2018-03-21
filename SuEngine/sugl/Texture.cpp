#include "Texture.h"

//#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

Texture2D::Texture2D(const std::string & fileName)
{
	loadPicToGL(fileName);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_textureObject);
}

void Texture2D::use(GLenum textureUnit)
{
	//set the texture to Unit 0 first, but this will have to use with shader togehter
	//GLuint big_tex_loc = glGetUniformLocation(m_glProgram.GetProgram(), "quat_tex");
	//glUniform1i(big_tex_loc, 0);

	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, m_textureObject);
}

void Texture2D::loadPicToGL(const std::string &fileName)
{
	//Su::file::readImage_BMP(outInfo, fileName.data());
	int width, height, channels;
	unsigned char *data = stbi_load(fileName.c_str(), &width, &height, &channels, STBI_rgb_alpha);
	if (!data)
	{
		fprintf(stderr, "The file of texture do not exist, or not a correct image file.");
		return;
	}

	glGenTextures(1, &m_textureObject);
	glBindTexture(GL_TEXTURE_2D, m_textureObject);

	if (data)
	{
		if (channels == 3) //for image that only have 3 channels
			// the first GL_RGB is the internal format that we wish to save in OpenGL
			// the second one is the image's data's format
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else if (channels == 4)// for image that have alpha channels
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glGenerateMipmap(GL_TEXTURE_2D);
}
