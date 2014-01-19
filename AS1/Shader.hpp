#ifndef SHADER_H
#define SHADER_H

#include <istream>
#include "GL/gl_core_3_3.h"

class ShaderProgram
{
public:
    //Construct from given vertex and fragment sources
    ShaderProgram(std::istream &vert, std::istream &frag);
    //Construct from given vertex and fragment files
    ShaderProgram(const char* vert, const char* frag);

    //free resources associated with this program
    ~ShaderProgram();

    //Enable this program for rendering
    void use();

    //get a uniform
    GLint GetUniformLocation(const char* name);

private:
    //the actual GL program reference
    GLuint program;
    void init(std::istream &vert, std::istream &frag);

    //object is not copyable
    ShaderProgram(const ShaderProgram&);
};

#endif