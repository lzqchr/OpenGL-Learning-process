#include"Render.h"

void GLClearError(){
    while (glGetError() != GL_NO_ERROR);
}

//���drawcall ����log��Ϣ
bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "Opengl Error(" << error << "):" << function <<
            "\n" << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

Render::Render()
{
}

Render::~Render()
{
}

void Render::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();  
   // shader.SetUniform4("u_Color", r, 0.3f, 0.8f, 1.0f);
    va.Bind();
    ib.Bind();//����Ҳ�� ibo �� vao��һ���
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Render::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}
