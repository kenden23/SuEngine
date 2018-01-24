#include "Triangle.h"
#include "controllers/Camera.h"

Triangle::Triangle() : TriView()
, m_pCamera(nullptr)
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
	if (!initCamera())
	{
		return false;
	}
	return true;
}

void Triangle::update(double dt)
{
	m_glProgram.Enable();

	m_pCamera->update((float)dt);

	glm::mat4 pr =  glm::perspective(glm::radians(45.f), 4.0f / 3.0f, 0.1f, 100.0f);

	glm::mat4 vm = glm::lookAt(
		glm::vec3(13, 13, 13),			// Camera is here
		glm::vec3(0, 0, 0),// and looks here : at the same position, plus "direction"
		glm::vec3(0, 1, 0)					// Head is up (set to 0,-1,0 to look upside-down)
	);

	auto loc = m_glProgram.GetUniformLocation("mvp");

	m_glProgram.SetUniformMat4(loc, m_pCamera->GetViewProj());
	//m_glProgram.SetUniformMat4(loc, glm::mat4(1));
}

void Triangle::render(double dt)
{
	renderView(dt);
}

bool Triangle::initCamera()
{
	if (!m_pCamera)
	{
		m_pCamera = new Camera();
	}
	m_pCamera->init(SuFw::GetInstance()->getWin());

	return true;
}
