#pragma once

#include "sugl/SuGlFunc.h"
#include "sugl/SuGlfw.h"

#include "TriView.h"


class Triangle :public TriView
{
public:
	Triangle();
	~Triangle();

	bool init();
	void update(double dt);
	void render(double dt);
protected:

private:
};