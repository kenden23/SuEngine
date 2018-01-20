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
#include "GL/glew.h"

#include "GLFW/glfw3.h"

// include this header to get better hint for gl functions
// or include this header to the visual assist c/c++ directories
//#include "GL/glext.h"

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <chrono>

// Include GLM
#include "glm.hpp"

#include "render/GLProgram.h"

#include "SimpleTest/triangles/Triangle.h"
#include "SimpleTest/drawers/MultiLinesView.h"

int main(void)
{
	SuFw::GetInstance()->basicInit();
	GLFWwindow *pWin = SuFw::GetInstance()->getWin();
	SuFw::GetInstance()->initGlfwEvents();

	//return SuFw::GetInstance()->run(pWin1);

	//return 0;

	Triangle tri;
	tri.init();

	MultiLinesView mlv;
	mlv.initView();
	mlv.initShader();

	// Initialise GLFW
	//if (!glfwInit())
	//{
	//	fprintf(stderr, "Failed to initialize GLFW\n");
	//	getchar();
	//	exit(-1);
	//}

	// Open a window and create its OpenGL context
	//GLFWwindow *pWin = glfwCreateWindow(1024, 780, "12313", NULL, NULL);
	//if (!pWin) {
	//	fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 ////compatible. Try the 2.1 version of the tutorials.\n");
	//	getchar();
	//	glfwTerminate();
	//	exit(-1);
	//}
	//glfwMakeContextCurrent(pWin);
	//
	//// Initialize GLEW
	//glewExperimental = true; // Needed for core profile
	//if (glewInit() != GLEW_OK) {
	//	fprintf(stderr, "Failed to initialize GLEW\n");
	//	getchar();
	//	glfwTerminate();
	//	exit(-2);
	//}
	//// Ensure we can capture the escape key being pressed below
	//glfwSetInputMode(pWin, GLFW_STICKY_KEYS, GL_TRUE);

	glfwMakeContextCurrent(pWin);
	glClearColor(.1f, 0.5f, 0.1f, 0.f);

	double dt = 60.0 / 1000.0;

	mlv.addTwoPoints(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
	mlv.addPoint(glm::vec3(0.f, 0.f, 0.f));
	mlv.addPoint(glm::vec3(1.f, 0.f, 0.f));

	do {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		//tri.update(dt);

		//tri.render(dt);

		mlv.renderView(dt);

		// Swap buffers
		//glfwSwapBuffers(pWin);
		//glfwPollEvents();

		SuFw::GetInstance()->glfwSwapPoll();

		std::this_thread::sleep_for(std::chrono::duration<double>(dt));
	} // Check if the ESC key was pressed or the window was closed
	while (SuFw::GetInstance()->isRunning());

	SuFw::GetInstance()->glfwEnd();

	return 0;
}

