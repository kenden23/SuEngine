/*************************************************************************
Copyright (c) 2017-2018 Su Jingxin (Bill Su)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN false EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <string>

#include "GLProgram.h"

#include "../file/SuFile.h"
#include "../utils/macros.h"

GLProgram::GLProgram() : m_program(0)
{
}


GLProgram::~GLProgram()
{
	if (m_program != 0)
	{
		glDeleteProgram(m_program);
		m_program = 0;
	}
}


bool GLProgram::Init()
{
	m_program = glCreateProgram();

	if (m_program == 0) {
		fprintf(stderr, "Error creating shader program\n");
		return false;
	}

	return true;
}

// Use this method to add shaders to the program. When finished - call finalize()
GLuint GLProgram::AddShader(GLenum ShaderType, const char* pFilename, bool deleteShaderAdded)
{
	std::string s;

	if (!Su::file::read(s, pFilename)) {
		return 0;
	}

	GLuint shader = glCreateShader(ShaderType);

	if (shader == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
		return 0;
	}

	const GLchar* p[1];
	p[0] = s.c_str();
	GLint Lengths[1] = { (GLint)s.size() };

	glShaderSource(shader, 1, p, Lengths);

	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(shader, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling '%s': '%s'\n", pFilename, InfoLog);
		return 0;
	}

	glAttachShader(m_program, shader);
	if (deleteShaderAdded)
	{
		glDeleteShader(shader);
		shader = 0;
	}
	return shader;
}

// After all the shaders have been added to the program call this function
// to link and validate the program.
bool GLProgram::Finalize()
{
	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	glLinkProgram(m_program);

	glGetProgramiv(m_program, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(m_program, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		return false;
	}

	glValidateProgram(m_program);
	glGetProgramiv(m_program, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(m_program, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		//   return false;
	}

	return GLCheckError();
}


void GLProgram::Enable()
{
	glUseProgram(m_program);
}


GLint GLProgram::GetUniformLocation(const char* pUniformName)
{
	GLuint Location = glGetUniformLocation(m_program, pUniformName);

	if (Location == INVALID_UNIFORM_LOCATION) {
		fprintf(stderr, "Warning! Unable to get the location of uniform '%s'\n", pUniformName);
	}

	return Location;
}

GLint GLProgram::GetProgramParam(GLint param)
{
	GLint ret;
	glGetProgramiv(m_program, param, &ret);
	return ret;
}
