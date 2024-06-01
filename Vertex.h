#pragma once

#ifndef VERTEX_H
#define VERTEX_H

#include <gmtl/gmtl.h>
#include <gmtl/Matrix.h>

struct Vertex {
	gmtl::Vec3f Position;
	gmtl::Vec3f Color; // Color
	gmtl::Vec2f UV;	// Uv coords
};

#endif // !VERTEX_H


