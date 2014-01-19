#ifndef OBJECT_H
#define OBJECT_H

#include "GL/gl_core_3_3.h"

class Object
{
public:
    //initialize with default triangle
    Object();

    //initialize from file
    //Object(std::istream &src)

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

    //object is not copyable
    Object(const Object&);
};

#endif