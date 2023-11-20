#include "VertexBuffer.h"

#include "Render.h"


VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_RendererID));//����������
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));//ѡ�񻺳���
    GLCall(glBufferData(GL_ARRAY_BUFFER,size, data, GL_STATIC_DRAW));//д�뻺����
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
