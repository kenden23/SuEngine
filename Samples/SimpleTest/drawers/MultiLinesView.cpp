#include "MultiLinesView.h"

#include "GL/glext.h"

#include "SegmentObj.h"

MultiLinesView::MultiLinesView() : m_vta(), m_glProgram()
, m_bAddNewPoint(false)
, m_bClearAllPoints(false)
, m_bDeletePoint(false)
, m_allPoints()
, m_pSegment(new SegmentObj)
{
	m_pSegment->initView();
	m_pSegment->initShader();

	std::function<void(GLFWwindow* window, int button, int action, int mods)> aFunc = std::bind(
	&MultiLinesView::mouseCB, this, std::placeholders::_1, std::placeholders::_2,
		std::placeholders::_3, std::placeholders::_4);
	EventInst->RegListener(aFunc, EventSys_glfwMouseButtonCallback, "MultiLinesView");
}

MultiLinesView::~MultiLinesView()
{
	EventInst->UnregListener(EventSys_glfwMouseButtonCallback, "MultiLinesView");

	if (m_pSegment)
	{
		delete m_pSegment;
		m_pSegment = nullptr;
	}
}

bool MultiLinesView::initView()
{
	setClearAllPointsState(true);
	return true;
}

bool MultiLinesView::initShader()
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

void MultiLinesView::renderView(double dt)
{
	if (!updatePoints())
	{
		return;
	}

	if (m_pSegment->isShow())
	{
		double x, y;
		SuFw::GetInstance()->get2DGLPosition(&x, &y);
		m_pSegment->setPosition(1, glm::vec3((float)x, (float)y, 0.f));

		m_pSegment->renderView(dt);
	}

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
	glDrawArrays(GL_LINES, 0, m_allPoints.size()); // 3 indices starting at 0 -> 1 triangle
	glDisableVertexAttribArray(0);
}

void MultiLinesView::addPoint(glm::vec3 &p)
{
	m_allPoints.push_back(p);
	if (m_allPoints.size() & 1)
	{
		addOddPointEffect(p);
	}
	else
	{
		addEvenPointEffect(p);
	}
}

void MultiLinesView::addOddPointEffect(glm::vec3 &p)
{
	m_pSegment->show(true);
	m_pSegment->setPosition(0, p);
	m_pSegment->setPosition(1, p);
}

void MultiLinesView::addEvenPointEffect(glm::vec3 &p)
{
	setAddNewPointState(true);
	m_pSegment->show(false);
}

void MultiLinesView::addTwoPoints(glm::vec3 &p1, glm::vec3 &p2)
{
	m_allPoints.push_back(p1);
	m_allPoints.push_back(p2);
	setAddNewPointState(true);
}

bool MultiLinesView::updatePoints()
{
	if (!isNeededUpdate())
	{
		return !m_allPoints.empty();
	}
	clearUpdateState();

	if (m_allPoints.empty())
	{
		return false;
	}
	
	if (glIsBuffer(m_vta.vbo))
	{
		glDeleteBuffers(1, &m_vta.vbo);
	}
	glGenBuffers(1, &m_vta.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vta.vbo);

	glBufferData(GL_ARRAY_BUFFER, m_allPoints.size() * sizeof(glm::vec3),
		&m_allPoints[0], GL_DYNAMIC_DRAW/*GL_STATIC_DRAW*/);

	return true;
}

enum MOUSECB_STATE
{
	MOUSE_STATE_CLICK,
	MOUSE_STATE_PRESS,
	MOUSE_STATE_RELEASE
};

void MultiLinesView::mouseCB(GLFWwindow* window, int button, int action, int mods)
{
	static MOUSECB_STATE curState = MOUSE_STATE_RELEASE;
	static MOUSECB_STATE lastState = curState;

	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
	{
		if (action == GLFW_PRESS)
		{
			double x, y;
			SuFw::GetInstance()->get2DGLPosition(&x, &y);
			addPoint(glm::vec3((float)x, (float)y, 0.f));
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

void MultiLinesView::setAddNewPointState(bool bAdded)
{
	m_bAddNewPoint = bAdded;
}

void MultiLinesView::setClearAllPointsState(bool bCleared)
{
	m_bClearAllPoints = bCleared;
}

void MultiLinesView::setDeletPointState(bool bDelete)
{
	m_bDeletePoint = bDelete;
}
