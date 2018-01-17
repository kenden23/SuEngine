#include "SegmentObj.h"

#include "GL/glext.h"

SegmentObj::SegmentObj() : m_vta(), m_glProgram()
, m_bNeededUpdate(false)
, m_pTwoPoints(new glm::vec3[POINT_NUM])
, m_bShow(false)
{
	m_pTwoPoints[0] = glm::vec3(0);
	m_pTwoPoints[1] = glm::vec3(0);

	std::function<void(GLFWwindow* window, int button, int action, int mods)> aFunc = std::bind(
		&SegmentObj::mouseCB, this, std::placeholders::_1, std::placeholders::_2,
		std::placeholders::_3, std::placeholders::_4);
	EventInst->RegListener(aFunc, EventSys_glfwMouseButtonCallback, "SegmentObj");
}

SegmentObj::~SegmentObj()
{
	EventInst->UnregListener(EventSys_glfwMouseButtonCallback, "SegmentObj");

	if (m_pTwoPoints)
	{
		delete[] m_pTwoPoints;
		m_pTwoPoints = nullptr;
	}
}

bool SegmentObj::initView()
{
	glGenBuffers(1, &m_vta.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vta.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * POINT_NUM, m_pTwoPoints, GL_DYNAMIC_DRAW);

	show(false);

	return true;
}

bool SegmentObj::initShader()
{
	if (!m_glProgram.Init())
	{
		return false;
	}
	if (!m_glProgram.AddShader(GL_VERTEX_SHADER, "shaders/shader.vs"))
	{
		return false;
	}
	if (!m_glProgram.AddShader(GL_FRAGMENT_SHADER, "shaders/shader.fs"))
	{
		return false;
	}
	m_glProgram.Finalize();

	m_glProgram.Enable();
	return true;
}

void SegmentObj::renderView(double dt)
{
	if (!isShow())
	{
		return;
	}

	updatePoints();

	glBindBuffer(GL_ARRAY_BUFFER, m_vta.vbo);
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,// attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	glDrawArrays(GL_LINES, 0, POINT_NUM); // 3 indices starting at 0 -> 1 triangle
	glDisableVertexAttribArray(0);
}

void SegmentObj::setPosition(int i, glm::vec3 &p)
{
	updatePoint(i, p);
}

void SegmentObj::moveTo(int i, glm::vec3 &deltaPoint)
{
	if (i < 0 || int(POINT_NUM) <= i)
	{
		return;
	}
	m_pTwoPoints[i] += deltaPoint;
	SetNeededUpdate(true);
}

void SegmentObj::updatePoint(int i, glm::vec3 &p)
{
	if (i < 0 ||(int) POINT_NUM <= i)
	{
		return;
	}
	m_pTwoPoints[i] = p;
	SetNeededUpdate(true);
}

void SegmentObj::updateTwoPoint(std::vector<glm::vec3> &pts)
{
	m_pTwoPoints[0] = pts[0];
	m_pTwoPoints[1] = pts[1];
	SetNeededUpdate(true);
}

void SegmentObj::show(bool bShow)
{
	m_bShow = bShow;
}

void SegmentObj::updatePoints()
{
	if (!isNeededUpdate())
	{
		return;
	}
	SetNeededUpdate(false);


//#define USING_MAP_BUFFER_RANGE_FOR_OP

#ifdef USING_MAP_BUFFER_RANGE_FOR_OP
	glm::vec3 * p = (glm::vec3 *)glMapBufferRange(
		GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * POINT_NUM,
		GL_MAP_WRITE_BIT/* | GL_MAP_INVALIDATE_BUFFER_BIT*/);

	memcpy(p, m_pTwoPoints, sizeof(glm::vec3) * POINT_NUM);

	glUnmapBuffer(GL_ARRAY_BUFFER);
#else
	if (glIsBuffer(m_vta.vbo))
	{
		glDeleteBuffers(1, &m_vta.vbo);
	}
	glGenBuffers(1, &m_vta.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vta.vbo);

	glBufferData(GL_ARRAY_BUFFER, POINT_NUM * sizeof(glm::vec3),
		m_pTwoPoints, GL_DYNAMIC_DRAW);
#endif

}

enum MOUSECB_STATE
{
	MOUSE_STATE_CLICK,
	MOUSE_STATE_PRESS,
	MOUSE_STATE_RELEASE
};

void SegmentObj::mouseCB(GLFWwindow* window, int button, int action, int mods)
{
	static MOUSECB_STATE curState = MOUSE_STATE_RELEASE;
	static MOUSECB_STATE lastState = curState;

	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
	{
		if (action == GLFW_PRESS)
		{
			double sx, sy;
			int w, h;
			//glfwGetCursorPos(window, &sx, &sy);
			SuFw::GetInstance()->glfwGetCurPos(&sx, &sy);
			//glfwGetWindowSize(window, &w, &h);
			SuFw::GetInstance()->getWinWideHeight(&w, &h);
			float x = sx / (float)w;
			float y = sy / (float)h;
			x = x * 2.f - 1.f;
			y = 1.f - y;
			y = y * 2.f - 1.f;
			//addPoint(glm::vec3(x, y, 0.f));
		}
		else if (GLFW_RELEASE == action)
		{

		}
		break;
	}
	default:
		break;
	}
}
