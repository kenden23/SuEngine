#include "MultiLinesView.h"

#include "GL/glext.h"

MultiLinesView::MultiLinesView() : m_vta(), m_glProgram()
, m_bAddNewPoint(false)
, m_bClearAllPoints(false)
, m_bDeletePoint(false)
, m_allPoints()
{

}

MultiLinesView::~MultiLinesView()
{

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
	setAddNewPointState(true);
}

void MultiLinesView::addTwoPoints(glm::vec3 &p1, glm::vec3 &p2)
{
	m_allPoints.push_back(p1);
	m_allPoints.push_back(p2);
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
