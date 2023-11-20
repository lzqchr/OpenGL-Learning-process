#include "Shader.h"


#include <iostream>
#include<fstream>
#include<string>
#include<sstream>

#include"Render.h"


//����shaderԴ��
ShaderProgramSource Shader::ParseShader(const std::string& filepath) {

    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line)) {

        if (line.find("#shader") != std::string::npos)//a�Ƿ��ҵ����
        {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(),ss[1].str() };
}

//���� ����shader����
unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);//����shader
    const char* src = source.c_str();//����һ��null��β�Ĳ��ɱ������ָ��
    glShaderSource(id, 1, &src, nullptr);//����shader
    glCompileShader(id);//����shader����

    // TODO: Rrror handing
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);//�᷵�� ������ֵ ���忴lib
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "����" << (type == GL_VERTEX_SHADER ? "VertexShader" : "FragmentShader") << "ʧ��" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }


    return id;
}

unsigned int Shader::CreatShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    //�������c++����һ�� �ȱ���֮������

    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);//����
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);//����ִ�д���

    glDeleteShader(vs);//����ɾ Ҳ���Բ�ɾ ��ò�ɾ
    glDeleteShader(fs);

    return program;
}


Shader::Shader(const std::string& filePath)
	:m_FilePath(filePath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(filePath);
    m_RendererID = CreatShader(source.VertexSource, source.FragmentSource);
    std::cout << "Vertex" << std::endl;
    std::cout << source.VertexSource << std::endl;
    std::cout << "Fragment" << std::endl;
    std::cout << source.FragmentSource << std::endl;
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    GLCall(glUniform1f(GetUniformLocation(name), value));
}


void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
    GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetUniform3f(const std::string& name, glm::vec3& value)
{
    GLCall(glUniform3f(GetUniformLocation(name), value.x,value.y,value.z));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform4f(const std::string& name, glm::vec4& value)
{
    GLCall(glUniform4f(GetUniformLocation(name),value.x,value.y,value.z,value.w));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    GLCall( glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}


 int Shader::GetUniformLocation(const std::string& name)
{
     if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
         return m_UniformLocationCache[name];


    GLCall( int location = glGetUniformLocation(m_RendererID, name.c_str()));//����u����
    if (location == -1)
        std::cout << "Warning:uniform ' " << name << " ' doesn't existl!" << std::endl;

    m_UniformLocationCache[name] = location;
    return location;
}

