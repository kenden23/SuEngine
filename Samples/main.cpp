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
#include <stdlib.h>
#include <thread>
#include <chrono>

#include "GL/glew.h"

#include "GLFW/glfw3.h"

// include this header to get better hint for gl functions
// or include this header to the visual assist c/c++ directories
//#include "GL/glext.h"

// Include GLM
#include "glm.hpp"

#include "render/GLProgram.h"
#include "sugl/SuWin.h"

#include "SimpleTest/triangles/Triangle.h"
#include "SimpleTest/drawers/MultiLinesView.h"

int main__(void)
{
	SuFw::GetInstance()->basicInit();
	GLFWwindow *pWin = SuFw::GetInstance()->getWin();
	SuFw::GetInstance()->initGlfwEvents();

	//Triangle tri;
	//tri.init();
	SuWin suw;
	suw.init();

	//MultiLinesView mlv;
	//mlv.initView();
	//mlv.initShader();

	glClearColor(.1f, 0.2f, 0.1f, 0.f);

	double dt = 60.0 / 1000.0;

	//mlv.addTwoPoints(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
	//mlv.addPoint(glm::vec3(0.f, 0.f, 0.f));
	//mlv.addPoint(glm::vec3(1.f, 0.f, 0.f));

	do {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		//tri.update(dt);
		suw.update(dt);

		//tri.render(dt);
		suw.render(dt);

		//mlv.renderView(dt);

		SuFw::GetInstance()->glfwSwapPoll();

		std::this_thread::sleep_for(std::chrono::duration<double>(dt));
	} // Check if the ESC key was pressed or the window was closed
	//while (SuFw::GetInstance()->isRunning());
	while (glfwGetKey(pWin, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		!glfwWindowShouldClose(pWin));

	SuFw::GetInstance()->glfwEnd();

	return 0;
}

