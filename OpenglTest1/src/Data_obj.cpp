#include"Data_obj.h"

SSBO::SSBO(const void* data, unsigned int size)
{
    glGenBuffers(1, &ID);
    // �󶨻������
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ID);
    // �����ڴ�ռ�
    glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_DYNAMIC_COPY);
    // ���������󶨵��󶨵���
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ID);
    // ��󻺳����
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