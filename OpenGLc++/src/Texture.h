#pragma once

#include "Render.h"

class Texture
{
public:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

private:

public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0)const;
	void UnBind()const;

	inline int GetWidth()const { return m_Width; }
	inline int GetHeight()const { return m_Height; }
	

};
