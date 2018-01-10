#include "Triangle.h"

Triangle::Triangle() : TriView()
{

}

Triangle::~Triangle()
{

}

bool Triangle::init()
{
	if (!initView())
	{
		return false;
	}
	if (!initShader())
	{
		return false;
	}
	return true;
}

void Triangle::update(double dt)
{

}

void Triangle::render(double dt)
{
	renderView(dt);
}
