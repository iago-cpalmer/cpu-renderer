#pragma once

#ifndef VERTEX_H
#define VERTEX_H

#include <gmtl/gmtl.h>
#include <gmtl/Matrix.h>

struct Vertex {
	gmtl::Vec3f Position;
	gmtl::Vec3f Color;
	gmtl::Vec2f UV;
};

// Vertex output by Geometry Pass
struct VertexGP {
	gmtl::Vec3f Position;
	gmtl::Vec3f Color;
	gmtl::Vec2f UV;
	uint32_t	MaterialId;
};

#endif // !VERTEX_H


