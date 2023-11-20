#include "IndexBuffer.h"

#include"Render.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    :m_Count(count)
{
    ASSERT(sizeof(unsigned int )== sizeof(GLuint))

    GLCall(glGenBuffers(1, &m_RendererID));//创建缓冲区
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));//选择缓冲区
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER,count*sizeof(unsigned int),data, GL_STATIC_DRAW));//写入缓冲区
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1,& m_RendererID));
}

void IndexBuffer::Bind()const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind()const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}
