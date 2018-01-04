#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "../SuEngine.h"

class SU_API SuFw
{
	SuFw();
	~SuFw();
public:
	SuFw *GetInstance();

	void basicInit(int width = 1024, int height = 768, const char *title = "SuEngine");
	void init2(int width = 1024, int height = 768, const char *title = "SuEngine");
	
	void glfwSwapPoll();

	// The same as get m_pWin and use glfw function to get windows wide and height.
	void getWinWideHeight(int *width, int *height);
	void getFrameBufWideHeight(int *width, int *height);

	GLFWwindow *getWin();
private:
	GLFWwindow *m_pWin;
};

