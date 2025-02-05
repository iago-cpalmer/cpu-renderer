#include "Mesh.h"

// ====================================
// Public
// ====================================

// ------------------------------------
// Constructor
// ------------------------------------
Mesh::Mesh(int r_vertex_buffer_initial_capacity, int r_index_buffer_initial_capacity)
	: m_vbo(r_vertex_buffer_initial_capacity)
	, m_ibo(r_index_buffer_initial_capacity)
	, m_vertex_count(0)
	, m_index_count(0)
{
	
}

// ------------------------------------
// Methods
// ------------------------------------
void Mesh::AddVertex(const Vertex r_vertex)
{
	if (m_vertex_count < m_vbo.size())
	{
		m_vbo[m_vertex_count] = r_vertex;
	}
	else
	{
		m_vbo.push_back(r_vertex);
	}
	m_vertex_count++;
}

void Mesh::AddIndex(const int r_index)
{
	if(m_index_count < m_ibo.size())
	{ 
		m_ibo[m_index_count] = r_index;
	}
	else
	{
		m_ibo.push_back(r_index);
	}
	m_index_count++;
}

void Mesh::ClearBuffers()
{
	m_vertex_count = 0;
	m_index_count = 0;
}

int Mesh::GetVertexCount()
{
	return m_vertex_count;
}

int Mesh::GetIndexCount()
{
	return m_index_count;
}

inline Vertex& Mesh::GetVertexAt(int r_index)
{
	assert(r_index < m_vertex_count);
	return m_vbo[r_index];
}

inline int& Mesh::GetIndexAt(int r_index)
{
	assert(r_index < m_index_count);
	return m_ibo[r_index];
}
