#include "VertexBuffer.h"

#include "Render.h"


VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_RendererID));//创建缓冲区
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));//选择缓冲区
    GLCall(glBufferData(GL_ARRAY_BUFFER,size, data, GL_STATIC_DRAW));//写入缓冲区
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind()const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind()const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
