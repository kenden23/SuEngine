#pragma once

#include "sugl/SuGlfw.h"
#include "sugl/SuGlFunc.h"

#include "TriView.h"

class Camera;

class Triangle :public TriView
{
public:
	Triangle();
	~Triangle();

	bool init();
	void update(double dt);
	void render(double dt);

protected:
	bool initCamera();

	Camera *m_pCamera;
private:
};