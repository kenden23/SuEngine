#include "SuWin.h"

#include "glm.hpp"
#include "../controllers/Camera.h"

//#include "GL/glext.h";

SuWin::SuWin() : m_vta(), m_glProgram()
, m_pCamera(nullptr)
{

}

SuWin::~SuWin()
{

}

bool SuWin::init()
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

void SuWin::update(double dt)
{
	m_glProgram.Enable();

	m_pCamera->update((float)dt);

	glm::mat4 pr = glm::perspective(glm::radians(45.f), 4.0f / 3.0f, 0.1f, 100.0f);

	glm::mat4 vm = glm::lookAt(
		glm::vec3(13, 13, 13),			// Camera is here
		glm::vec3(0, 0, 0),// and looks here : at the same position, plus "direction"
		glm::vec3(0, 1, 0)					// Head is up (set to 0,-1,0 to look upside-down)
	);

	auto loc = m_glProgram.GetUniformLocation("mvp");

	m_glProgram.SetUniformMat4(loc, m_pCamera->GetViewProj());
	//m_glProgram.SetUniformMat4(loc, glm::mat4(1));
}

void SuWin::render(double dt)
{
	renderView(dt);
}

bool SuWin::initView()
{
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	//static const GLfloat g_vertex_buffer_data[] = {
	//	-100.f, 0.f, -100.f,
	//	100.f, 0.f, -100.f,
	//	-100.f, 0.f, 100.f
	//
	//	//10000, 0, 10000,
	//	//-10000, 0, 10000,
	//	//10000, 0, -10000
	//};

	glGenBuffers(1, &m_vta.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vta.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	return true;
}

bool SuWin::initShader()
{
	if (!m_glProgram.Init())
	{
		return false;
	}
	if (!m_glProgram.AddShader(GL_VERTEX_SHADER, "shaders/shader_trans.vs"))
	{
		return false;
	}
	if (!m_glProgram.AddShader(GL_FRAGMENT_SHADER, "shaders/shader_trans.fs"))
	{
		return false;
	}
	m_glProgram.Finalize();

	m_glProgram.Enable();
	return true;
}

void SuWin::renderView(double dt)
{
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

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle
	glDisableVertexAttribArray(0);
}

bool SuWin::initCamera()
{
	if (!m_pCamera)
	{
		m_pCamera = new Camera();
	}
	m_pCamera->init(SuFw::GetInstance()->getWin());

	return true;
}
