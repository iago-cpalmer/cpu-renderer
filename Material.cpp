#include "Material.h"

Material Material::NULL_MATERIAL{};

Material::Material(Texture* rp_tex)
	: m_texture_id(UINT_UNASSIGNED)
	, m_material_id(UINT_UNASSIGNED)
{
	if (rp_tex != nullptr)
	{
		m_texture_id = rp_tex->GetId();
	}

}

Material::Material()
	: m_material_id(UINT_UNASSIGNED)
	, m_texture_id(UINT_UNASSIGNED)
{

}