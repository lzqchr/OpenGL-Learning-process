#include "mTexture.h"
#include"vendor/std_image/stb_image.h"

mTexture::mTexture(const std::string& path,bool mipmap)
	:m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), 
	m_Width(0), m_Height(0), m_BPP(0)
{
	//opengl 从左下角开始加载  而png是从左上开始
	stbi_set_flip_vertically_on_load(1);//让数据垂直翻转
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);


	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	
	//贴图大小处理
	GLCall(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	//超过贴图 边界处理
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
	
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocalBuffer) {
		stbi_image_free(m_LocalBuffer);
	}
}

mTexture::mTexture(int m_width, int m_hidth):m_RendererID(0),m_LocalBuffer(nullptr),
m_Width(0), m_Height(0), m_BPP(0)
{
	glGenTextures(1, &m_RendererID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_width, m_hidth, 0, GL_RGBA, GL_FLOAT,
		NULL);
	//glBindImageTexture(index, m_RendererID, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
}

mTexture::mTexture(int m_width, int m_hidth, float* data):m_RendererID(0), m_LocalBuffer(nullptr),
m_Width(m_width), m_Height(m_hidth), m_BPP(0)
{
	glGenTextures(1, &m_RendererID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_width, m_hidth, 0, GL_RGBA, GL_FLOAT, data);

}

mTexture::~mTexture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void mTexture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void mTexture::cBind(unsigned int slot) const
{
	glBindImageTexture(slot, m_RendererID, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
}

void mTexture::UnBind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

 void mTexture::updateMipmap() {
	 glGenerateMipmap(GL_TEXTURE_2D);
 }

