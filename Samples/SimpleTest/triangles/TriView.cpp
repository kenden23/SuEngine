#include "TriView.h"

#include "glm.hpp"
#include "render/GLProgram.h"

//#include "GL/glext.h";

TriView::TriView() : m_vta(), m_glProgram()
{

}

TriView::~TriView()
{

}

bool TriView::initView()
{
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};
	glGenBuffers(1, &m_vta.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vta.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	return true;
}

bool TriView::initShader()
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

void TriView::renderView(double dt)
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

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle
	glDisableVertexAttribArray(0);
}
