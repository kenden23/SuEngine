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

#pragma once

#include <string>
#include <vector>

#include "glm.hpp"

#include "../SuEngine.h"

namespace Su
{

enum class ReadFileResultCode
{
	ReadFileResultNull,
	CannotOpenOrNoSuchFile,
	IncorrectFileFormat,
	CorruptFile,
	ReadFileSuccessfully,
};

struct SimpleImageInfo
{
	unsigned int width, height, channel;
	// allocate memory by alloc, and free by SimpleImageInfo destructor with free
	void *data;
	SimpleImageInfo() :width(0), height(0), data(nullptr)
	{

	}

	~SimpleImageInfo()
	{
		if (data)
		{
			free(data);
			data = nullptr;
		}
	}
};

namespace file
{

bool SU_API read(std::string &outStr, const char *fileName);

/// @return char *, memory is created by malloc, so free it with free(char *)
SU_API char *read(const char *fileName);

SU_API ReadFileResultCode readImage_BMP(SimpleImageInfo &outInfo, const char *fileName);

SU_API ReadFileResultCode readImage_stb(SimpleImageInfo &outInfo, const char *fileName);

SU_API ReadFileResultCode readAssimpData(const char * path,
	std::vector<unsigned short> & indices,
	std::vector<glm::vec3> & vertices,
	std::vector<glm::vec2> & uvs,
	std::vector<glm::vec3> & normals);

}

}
