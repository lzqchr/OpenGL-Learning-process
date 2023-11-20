#include "Shader.h"


#include <iostream>
#include<fstream>
#include<string>
#include<sstream>

#include"Render.h"


//分析shader源码
ShaderProgramSource Shader::ParseShader(const std::string& filepath) {

    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line)) {

        if (line.find("#shader") != std::string::npos)//a是否找到标记
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

//创建 编译shader程序
unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);//创建shader
    const char* src = source.c_str();//返回一个null结尾的不可变数组的指针
    glShaderSource(id, 1, &src, nullptr);//导入shader
    glCompileShader(id);//编译shader代码

    // TODO: Rrror handing
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);//会返回 各种数值 具体看lib
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "编译" << (type == GL_VERTEX_SHADER ? "VertexShader" : "FragmentShader") << "失败" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }


    return id;
}

unsigned int Shader::CreatShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    //就像编译c++代码一样 先编译之后链接

    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);//链接
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);//检查可执行代码

    glDeleteShader(vs);//可以删 也可以不删 最好不删
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


    GLCall( int location = glGetUniformLocation(m_RendererID, name.c_str()));//查找u变量
    if (location == -1)
        std::cout << "Warning:uniform ' " << name << " ' doesn't existl!" << std::endl;

    m_UniformLocationCache[name] = location;
    return location;
}

