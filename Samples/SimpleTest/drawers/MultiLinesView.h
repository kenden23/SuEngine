#pragma once

#include "sugl/SuGlFunc.h"
#include "sugl/SuGlfw.h"
#include "render/GLProgram.h"

#include "glm.hpp"
#include <vector>

class SegmentObj;

class MultiLinesView
{
public:
	MultiLinesView();
	~MultiLinesView();

//protected:
	virtual bool initView();

	virtual bool initShader();

	virtual void renderView(double dt);

	// add a point once, add two points two times to form a line
	// if the total points is odd, the last one will be ignored.
	void addPoint(glm::vec3 &p);
	void addTwoPoints(glm::vec3 &p1, glm::vec3 &p2);

	bool updatePoints();

	std::vector<glm::vec3> m_allPoints;

	inline bool isNeededUpdate()
	{
		return getAddNewPointState() || getDeletePointState() || getClearAllPointsState();
	}
	inline void clearUpdateState()
	{
		setAddNewPointState(false);
		setDeletPointState(false);
		setClearAllPointsState(false);
	}

	void mouseCB(GLFWwindow* window, int button, int action, int mods);

	void setAddNewPointState(bool bAdded);
	inline bool getAddNewPointState() { return m_bAddNewPoint; }
	// if a new point has been added, then we need to update the buffer
	bool m_bAddNewPoint;

	void setClearAllPointsState(bool bCleared);
	inline bool getClearAllPointsState() { return m_bClearAllPoints; }
	bool m_bClearAllPoints;

	void setDeletPointState(bool bDelete);
	inline bool getDeletePointState() { return m_bDeletePoint; }
	bool m_bDeletePoint;

	// whether or not need to render,
	// eg. not data, not line for rendering, that not need for rendering
	bool m_bNeedRender;

	Su::VertexArray m_vta;
	GLProgram m_glProgram;

	SegmentObj *m_pSegment;
};
