#ifndef GRAPHICS_BUFFER_H
#define GRAPHICS_BUFFER_H

#include <wtypes.h>
#include <cstdint>

struct GraphicsBuffer
{
	HBITMAP Hbm;
	uint32_t* Data;
};

GraphicsBuffer CreateGraphicsBuffer(int r_width, int r_height);


class GraphicBuffers
{
public:
	// --------------------------------
	// Constructor
	// --------------------------------

	GraphicBuffers(int r_width, int r_height);

	~GraphicBuffers();

	// --------------------------------
	// Functions
	// --------------------------------

	inline void Swap()
	{
		m_current_buffer_at_front = (m_current_buffer_at_front + 1) % TOTAL_BUFFERS;
	}

	inline HBITMAP GetFrontBuffer()
	{
		return Front().Hbm;
	}

	inline void Clear(COLORREF r_color)
	{
		memset(Back().Data, r_color, sizeof(uint32_t) * Size());
	}

	inline void SetPixel(int r_x, int r_y, COLORREF r_color)
	{
		if (r_x < 0 || r_x >= m_width || r_y < 0 || r_y >= m_height)
		{
			return;
		}
		Back().Data[r_y * m_width + r_x] = r_color;
	}

	inline int GetWidth() const
	{
		return m_width;
	}
	inline int GetHeight() const
	{
		return m_height;
	}


private:
	// --------------------------------
	// Constants
	// --------------------------------

	static constexpr int TOTAL_BUFFERS = 2;

	// --------------------------------
	// Variables
	// --------------------------------
	GraphicsBuffer m_buffers[TOTAL_BUFFERS];

	int m_width;
	int m_height;

	uint8_t m_current_buffer_at_front;

	// --------------------------------
	// Functions
	// --------------------------------ç

	inline size_t Size() const
	{
		return static_cast<size_t>(m_width * m_height);
	}

	inline GraphicsBuffer& Back()
	{
		return m_buffers[(m_current_buffer_at_front + 1) % TOTAL_BUFFERS];
	}

	inline GraphicsBuffer& Front()
	{
		return m_buffers[m_current_buffer_at_front];
	}

};

#endif // !GRAPHICS_BUFFER_H


