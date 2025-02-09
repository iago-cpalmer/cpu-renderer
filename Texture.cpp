#include "Texture.h"

#include <algorithm>
#include "GlobalDefs.h"

// ====================================
//  PUBLIC
// ====================================

// --------------------------------
//  Constructors
// --------------------------------
Texture::Texture(const char* file_name)
    : m_texture_id(UINT_UNASSIGNED)
{
    // Load image using stb_image
    mp_data = stbi_load(file_name, &m_width, &m_height, &m_channels, 0);

    if (!mp_data) {
        std::cerr << "Failed to load image: " << file_name << std::endl;
    }

    m_wrapping_mode = WrappingMode::CLAMP_TO_EDGE;
}

// --------------------------------
//  Functions
// --------------------------------

void Texture::SetWrappingMode(const WrappingMode r_wrapping_mode) noexcept
{
    m_wrapping_mode = r_wrapping_mode;
}

WrappingMode Texture::GetWrappingMode() noexcept
{
    return m_wrapping_mode;
}

COLORREF Texture::GetColorAtUV(float r_u, float r_v) noexcept
{
    switch (m_wrapping_mode)
    {
    case WrappingMode::CLAMP_TO_EDGE:
        r_u = std::clamp(r_u, 0.0f, 1.0f);
        r_v = std::clamp(r_v, 0.0f, 1.0f);
        break;
    case WrappingMode::REPEAT:
        r_u = std::fmodf(r_u, 1.0f);
        r_v = std::fmodf(r_v, 1.0f);
        break;
    }
    
    const int x = r_u * (m_width-1);
    const int y = r_v * (m_height-1);

    const int index = (y * m_width + x) * m_channels;

    return RGB(mp_data[index + 0], mp_data[index + 1], mp_data[index + 2]);
}

// ====================================
//  PRIVATE
// ====================================