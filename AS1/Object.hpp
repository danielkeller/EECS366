#ifndef OBJECT_H
#define OBJECT_H

#include "stdafx.h"

#include <vector>
#include <memory>

class ShaderProgram;

class Object
{
public:
    //initialize with default box
    Object();

    //initialize from file
    Object(const char* filename);

    //clear object's resources
    ~Object();

    //Draw object to screen
    void draw(const glm::mat4& transform);

private:
    //the GL vertex array object assocated with this object
    GLuint vertexArrayObject;

    //GL buffer objects for vertex and vertex index data
    GLuint positionBufferObject;
    GLuint indexBufferObject;

    //how many vertex indices we have
    GLsizei numVertecies;

    //our shader program. the convention here is that the vertex position attribute is in
    //location 0, and the modelview uniform is 'mat4x4 modelView'
    std::shared_ptr<ShaderProgram> program;

    //real initialization work
    void init(const std::vector<GLfloat>& verts, const std::vector<GLint>& indices);

    //object is not copyable
    Object(const Object&);
};

#endif