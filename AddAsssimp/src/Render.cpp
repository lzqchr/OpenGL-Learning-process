#include"Render.h"

void GLClearError(){
    while (glGetError() != GL_NO_ERROR);
}

//检查drawcall 弹出log消息
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
    ib.Bind();//不绑定也行 ibo 和 vao是一起的
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Render::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}
