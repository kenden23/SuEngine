#include "SuGlfw.h"

#include <stdio.h>
#include <stdlib.h>

SuFw::SuFw() : m_pWin(nullptr)
{

}

SuFw::~SuFw()
{

}

SuFw * SuFw::GetInstance()
{

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
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
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

void SuFw::glfwSwapPoll()
{
	// has to do both
	// show the back buffer
	glfwSwapBuffers(m_pWin);
	// poll events so that, window can go on working,
	// otherwise it will stuck here. window need to handle something here.
	glfwPollEvents();
}

void SuFw::glfwEnd()
{
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

void SuFw::getWinWideHeight(int *width, int *height)
{
	glfwGetWindowSize(m_pWin, width, height);
}

void SuFw::getFrameBufWideHeight(int *width, int *height)
{
	glfwGetFramebufferSize(m_pWin, width, height);
}

GLFWwindow * SuFw::getWin()
{
	return m_pWin;
}
