#include "stdafx.h"
#include "Shader.hpp"
#include <iostream>
#include <fstream>
#include <vector>

ShaderProgram::ShaderProgram(const char* vert, const char* frag)
{
    init(std::ifstream(vert), std::ifstream(frag));
}

ShaderProgram::ShaderProgram(std::istream &vert, std::istream &frag)
{
    init(vert, frag);
}

ShaderProgram::~ShaderProgram()
{
    //the program will be deleted once it is no longer part of an active rendering state
    glDeleteProgram(program);
}

void ShaderProgram::use()
{
    //set this program as current
    glUseProgram(program);

    //set as lines for purposes of this demo
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

GLint ShaderProgram::GetUniformLocation(const char* name)
{
    return glGetUniformLocation(program, name);
}

GLuint CreateShader(GLenum eShaderType, std::istream &t)
{
    //read the stream into a string
    t.seekg(0, std::ios::end);
    size_t size = static_cast<size_t>(t.tellg());
    std::string buffer(size, ' ');
    t.seekg(0);
    t.read(&buffer[0], size); 

    //create the shader object
    GLuint shader = glCreateShader(eShaderType);

    //attach and compile the source
    const GLchar *strFileData = buffer.c_str();
    glShaderSource(shader, 1, &strFileData, NULL);
    glCompileShader(shader);
    
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) //compile failed
    {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<GLchar> infoLog(infoLogLength + 1);

        //print error message
        glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog.data());
        std::cerr << "Compile failure in shader: " << infoLog.data() << "\n";
    }

    return shader;
}

void ShaderProgram::init(std::istream &vert, std::istream &frag)
{
    //create our empty program object
    program = glCreateProgram();

    GLuint vertShdr = CreateShader(GL_VERTEX_SHADER, vert);
    GLuint fragShdr = CreateShader(GL_FRAGMENT_SHADER, frag);

    //attach vertex and fragment shaders
    glAttachShader(program, vertShdr);
    glAttachShader(program, fragShdr);
    
    //link the program object
    glLinkProgram(program);

    //check for linker errors
    GLint status;
    glGetProgramiv (program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<GLchar> infoLog(infoLogLength + 1);

        glGetProgramInfoLog(program, infoLogLength, NULL, infoLog.data());
        std::cerr << "Linker failure: " << infoLog.data() << "\n";
    }

    //shaders are no longer used now that the program is linked
    glDetachShader(program, vertShdr);
    glDeleteShader(vertShdr);
    glDetachShader(program, fragShdr);
    glDeleteShader(fragShdr);
}