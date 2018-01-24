#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "../SuEngine.h"
#include "../event_sys/EventSys.h"

class SU_API SuFw
{
	SuFw();
	~SuFw();
public:
	static SuFw *GetInstance();

	void basicInit(int width = 1024, int height = 768, const char *title = "SuEngine");
	void init2(int width = 1024, int height = 768, const char *title = "SuEngine");

	void initGlfwEvents();

	int run(GLFWwindow *pWin);
	
	void glfwSwapPoll();
	bool glfwShouldClose();
	bool isRunning();

	// call this at the end, or cal glfw native functions, like glfwTerminate()
	void glfwEnd();

	void glfwGetCurPos(double *x, double *y);

	// The same as get m_pWin and use glfw function to get windows wide and height.
	void getWinWideHeight(int *width, int *height);
	void getFrameBufWideHeight(int *width, int *height);

	void get2DGLPosition(double *x, double *y);

	GLFWwindow *getWin();
private:
	GLFWwindow *m_pWin;
};

