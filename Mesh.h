#include <vector>
#include "Vertex.h"
#ifndef MESH_H
#define MESH_H

class Mesh
{
public:
	// ------------------------------------
	// Constructor
	// ------------------------------------
	Mesh(int r_vertex_buffer_initial_capacity, int r_index_buffer_initial_capacity);

	// ------------------------------------
	// Methods
	// ------------------------------------

	void AddVertex(const Vertex r_vertex);
	void AddIndex(const int r_index);

	void ClearBuffers();

	int GetVertexCount();
	int GetIndexCount();

	inline Vertex& GetVertexAt(int r_index);
	inline int& GetIndexAt(int r_index);

private:

	// ------------------------------------
	// Variables
	// ------------------------------------

	std::vector<Vertex> m_vbo;
	std::vector<int> m_ibo;

	int m_vertex_count;
	int m_index_count;
};

#endif // !MESH_H
