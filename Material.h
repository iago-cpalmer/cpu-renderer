#ifndef MATERIAL_H
#define MATERIAL_H

#include <cstdint>
#include "GlobalDefs.h"
#include "Texture.h"

struct Material
{
public:

	static Material NULL_MATERIAL;

	// -----------------------------------
	// Functions
	// -----------------------------------

	Material(Texture* rp_tex);

	inline IRuint GetMaterialId()
	{
		return m_material_id;
	}

	inline IRuint GetTextureId()
	{
		return m_texture_id;
	}

	inline void SetMaterialId(IRuint r_mat_id)
	{
		m_material_id = r_mat_id;
	}

private:
	// -----------------------------------
	// Variables
	// -----------------------------------

	IRuint m_material_id;
	IRuint m_texture_id;

	// Vertex shader function pointer
	// Fragment shader function pointer
	
	// -----------------------------------
	// Functions
	// -----------------------------------

	Material();

};


#endif // !MATERIAL_H

