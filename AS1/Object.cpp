#include "Object.hpp"

//default triangle data
const GLfloat vertexPositions[] = {
    0.75f, 0.75f, 0.0f, 1.0f,
    0.75f, -0.75f, 0.0f, 1.0f,
    -0.75f, 0.75f, 0.0f, 1.0f,
    -0.75f, -0.75f, 0.0f, 1.0f,
};

const GLint vertexIndices[] = {
    0, 1, 2, 1, 2, 3
};

Object::Object()
{
    //create a VAO for the object and bind it as current
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    //generate a new buffer object for positionBufferObject
    glGenBuffers(1, &positionBufferObject);

    //bind the newly-created buffer object positionBufferObject as the current GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
    //upload the data in vertexPositions to the current GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    //enable generic attribute array 0 in the current vertex array object (VAO)
    //this is referenced in the vertex shader as "layout(location = 0) in vec4 position;"
    glEnableVertexAttribArray(0);
    //associate the buffer data bound to GL_ARRAY_BUFFER with the attribute in index 0
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    //clear the currently bound GL_ARRAY_BUFFER; it has been associated with the VAO by
    //glVertexAttribPointer and GL will remember it
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    //generate a new buffer object for the vertex indices
    glGenBuffers(1, &indexBufferObject);

    //GL_ELEMENT_ARRAY_BUFFER binding is part of the current VAO state, therefore we do not unbind it
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices), vertexIndices, GL_STATIC_DRAW);
}

Object::~Object()
{
    //delete VAO and buffers
    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &positionBufferObject);
    glDeleteBuffers(1, &indexBufferObject);
}

void Object::draw()
{
    //make the objects VAO current. this brings in all the associated data.
    glBindVertexArray(vertexArrayObject);

    //set as lines for purposes of this demo
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    //draw verteces according to the index and position buffer objects
    //the final argument to this call is an integer offset, cast to pointer type. don't ask me why.
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, static_cast<void*>(0));
}