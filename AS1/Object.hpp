#ifndef OBJECT_H
#define OBJECT_H

#include "GL/gl_core_3_3.h"
#include <vector>

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
    void draw();

private:
    //the GL vertex array object assocated with this object
    GLuint vertexArrayObject;

    //GL buffer objects for vertex and vertex index data
    GLuint positionBufferObject;
    GLuint indexBufferObject;

    //how many vertex indices we have
    GLsizei numVertecies;

    //real initialization work
    void init(const std::vector<GLfloat>& verts, const std::vector<GLint>& indices);

    //object is not copyable
    Object(const Object&);
};

#endif