#pragma once

#include "Render.h"

class mTexture
{
public:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

private:

public:
	mTexture(const std::string& path,bool mipmap = false);
	mTexture(int m_width,int m_hidth);
	mTexture(int m_width, int m_hidth, float*  data);
	~mTexture();

	void Bind(unsigned int slot = 0)const;
	void cBind(unsigned int slot = 0)const;
	void UnBind()const;

	inline int GetWidth()const { return m_Width; }
	inline int GetHeight()const { return m_Height; }
	void updateMipmap();

};
