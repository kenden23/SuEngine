#pragma once

#include "SuGlfw.h"
#include "SuGlFunc.h"
#include "../render/GLProgram.h"

#include "../SuEngine.h"

class Camera;

class SU_API SuWin
{
public:
	SuWin();
	~SuWin();

	bool init();
	void update(double dt);
	void render(double dt);

protected:
	virtual bool initView();

	virtual bool initShader();

	virtual void renderView(double dt);

	virtual bool initCamera();

	Camera *m_pCamera;

	Su::VertexArray m_vta;
	GLProgram m_glProgram;
};