#include "Mesh.h"

// ====================================
// Public
// ====================================

// ------------------------------------
// Constructor
// ------------------------------------


Mesh::Mesh(int r_vertex_buffer_initial_capacity, int r_index_buffer_initial_capacity, Material& rp_mat)
	: m_vbo(r_vertex_buffer_initial_capacity)
	, m_ibo(r_index_buffer_initial_capacity)
	, m_vertex_count(0)
	, m_index_count(0)
	, m_material_id(rp_mat.GetMaterialId())
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
