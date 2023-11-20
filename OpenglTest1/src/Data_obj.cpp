#include"Data_obj.h"

SSBO::SSBO(const void* data, unsigned int size)
{
    glGenBuffers(1, &ID);
    // 绑定缓冲对象
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ID);
    // 分配内存空间
    glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_DYNAMIC_COPY);
    // 将缓冲对象绑定到绑定点上
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ID);
    // 解绑缓冲对象
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void SSBO::Update(const void* data, unsigned int size, unsigned int offset)
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ID);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, data);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

 void SSBO::Bind(unsigned int solt)
{
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, solt, ID);
}


SSBO::~SSBO()
{
  //  glDeleteBuffers(1, &ID);
}