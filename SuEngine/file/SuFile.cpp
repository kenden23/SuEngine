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


#include "SuFile.h"

namespace Su
{
namespace file
{

SU_API bool read(std::string &outStr, const char *fileName)
{
	char *tmp = read(fileName);
	if (!tmp)
	{
		return false;
	}
	outStr = tmp;
	free(tmp);
	return true;
}

SU_API char * read(const char *fileName)
{
	FILE *fp = fopen(fileName, "r");
	if (!fp) return nullptr;

	fseek(fp, 0, SEEK_END);
	int len = ftell(fp);
	if (len < 1)
	{
		return nullptr;
	}

	rewind(fp);
	char *tmp = (char *)malloc(sizeof(char) * (len + 1));
	tmp[len] = '\0';
	fread(tmp, sizeof(char), len, fp);
	fclose(fp);
	return tmp;
}

SU_API ReadFileResultCode readImage_BMP(SimpleImageInfo &outInfo, const char * fileName)
{
	unsigned char header[54] = {0};
	unsigned int dataPos = 0;
	unsigned int imageSize = 0;
	FILE *fp = fopen(fileName, "rb");
	if (!fp)
	{
		return ReadFileResultCode::CannotOpenOrNoSuchFile;
	}
	bool readCode = (fread(header, 1, 54, fp) == 54 && header[0] == 'B' && header[1] == 'M');
	//readCode = readCode && (*(int*)&(header[0x1E]) == 0);
	//readCode = readCode && (*(int*)&(header[0x1C]) == 24);
	if (!readCode)
	{
		fclose(fp);
		return ReadFileResultCode::IncorrectFileFormat;
	}
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	outInfo.width = *(int*)&(header[0x12]);
	outInfo.height = *(int*)&(header[0x16]);
	if (imageSize < 1)
	{
		// 3 : one byte for each Red, Green and Blue component
		imageSize = outInfo.width * outInfo.height * 3;
	}
	// The BMP header is done that way
	if (0 == dataPos)
	{
		dataPos = 54;
	}
	outInfo.data = (void *)malloc(imageSize);
	fread(outInfo.data, 1, imageSize, fp);
	fclose(fp);
	return ReadFileResultCode::ReadFileSuccessfully;
}

}
}