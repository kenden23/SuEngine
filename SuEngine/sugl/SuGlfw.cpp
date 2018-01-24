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
#include <assert.h>

#include "SuGlfw.h"

SuFw::SuFw() : m_pWin(nullptr)
{

}

SuFw::~SuFw()
{

}

SuFw * SuFw::GetInstance()
{
	static SuFw inst;
	return &inst;
}

void SuFw::basicInit(int width, int height, const char *title)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		exit(-1);
	}

	// Open a window and create its OpenGL context
	m_pWin = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!m_pWin) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 //compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(m_pWin);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		exit(-2);
	}
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(m_pWin, GLFW_STICKY_KEYS, GL_TRUE);
	glfwPollEvents();

	glClearColor(1.f, 0.f, 0.f, 1.f);
}

void SuFw::init2(int width, int height, const char *title)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		exit(-1);
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	m_pWin = glfwCreateWindow(width, height, title, NULL, NULL);
	if (m_pWin == NULL) {
		fprintf(stderr, "Failed to open GLFW window.\n");
		getchar();
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(m_pWin);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		exit(-2);
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(m_pWin, GLFW_STICKY_KEYS, GL_TRUE);
}

void SuFw::initGlfwEvents()
{
	//glfwSetWindowSizeCallback(m_pWin, glfw_onResize);
	//glfwSetKeyCallback(m_pWin, glfw_onKey);
	glfwSetMouseButtonCallback(m_pWin, [](GLFWwindow* window, int button, int action, int mods) {
		EventInst->FireEvent(EventSys_glfwMouseButtonCallback, window, button, action, mods);
	});
	//glfwSetCursorPosCallback(m_pWin, glfw_onMouseMove);
	//glfwSetScrollCallback(m_pWin, glfw_onMouseWheel);
}

int SuFw::run(GLFWwindow *pWin)
{
	assert(pWin);// , "Create Window First.");

	do {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		// add register functions here

		// Swap buffers
		glfwSwapBuffers(pWin);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(pWin, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(pWin) == 0);

	glfwTerminate();

	return 0;
}

void SuFw::glfwSwapPoll()
{
	// has to do both
	// show the back buffer
	glfwSwapBuffers(m_pWin);
	// poll events so that, window can go on working,
	// otherwise it will stuck here. window need to handle something here.
	glfwPollEvents();
}

bool SuFw::glfwShouldClose()
{
	return glfwGetKey(m_pWin, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
		glfwWindowShouldClose(m_pWin);
}

bool SuFw::isRunning()
{
	return glfwGetKey(m_pWin, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		!glfwWindowShouldClose(m_pWin);
}

void SuFw::glfwEnd()
{
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

void SuFw::glfwGetCurPos(double *x, double *y)
{
	glfwGetCursorPos(m_pWin, x, y);
}

void SuFw::getWinWideHeight(int *width, int *height)
{
	glfwGetWindowSize(m_pWin, width, height);
}

void SuFw::getFrameBufWideHeight(int *width, int *height)
{
	glfwGetFramebufferSize(m_pWin, width, height);
}

void SuFw::get2DGLPosition(double *x, double *y)
{
	double sx, sy;
	int w, h;
	glfwGetCursorPos(m_pWin, &sx, &sy);
	glfwGetWindowSize(m_pWin, &w, &h);
	sx = sx / (double)w;
	sy = sy / (double)h;
	*x = sx * 2.f - 1.f;
	*y = 1.f - sy;
	*y = *y * 2.f - 1.f;
}

GLFWwindow * SuFw::getWin()
{
	return m_pWin;
}
