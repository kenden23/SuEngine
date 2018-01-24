#pragma once

#include "sugl/SuGlfw.h"
#include "sugl/SuGlFunc.h"
#include "render/GLProgram.h"

#include "glm.hpp"

/*
Two points to define a segment.
*/
class SegmentObj
{
public:
	SegmentObj();
	~SegmentObj();

	enum {POINT_NUM = 2};

	//protected:
	virtual bool initView();

	virtual bool initShader();

	virtual void renderView(double dt);

	void setPosition(int i, glm::vec3 &p);
	void moveTo(int i, glm::vec3 &deltaPoint);

	void updatePoint(int i, glm::vec3 &p);
	void updateTwoPoint(std::vector<glm::vec3> &pts);

	void show(bool bShow);
	bool isShow() { return m_bShow; }

	void updatePoints();

	glm::vec3 *m_pTwoPoints;

	inline bool isNeededUpdate()
	{
		return m_bNeededUpdate;
	}
	inline void SetNeededUpdate(bool bUpdate) { m_bNeededUpdate = bUpdate; }
	bool m_bNeededUpdate;

	void mouseCB(GLFWwindow* window, int button, int action, int mods);

	// whether or not need to render,
	// eg. not data, not line for rendering, that not need for rendering
	bool m_bNeedRender;
	bool m_bShow;

	Su::VertexArray m_vta;
	GLProgram m_glProgram;
};
