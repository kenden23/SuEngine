#pragma once

#include "sugl/SuGlFunc.h"
#include "sugl/SuGlfw.h"
#include "render/GLProgram.h"

class TriView
{
public:
	TriView();
	~TriView();

protected:
	virtual bool initView();

	virtual bool initShader();

	virtual void renderView(double dt);

	Su::VertexArray m_vta;
	GLProgram m_glProgram;
};
