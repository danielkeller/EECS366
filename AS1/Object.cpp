#include "stdafx.h"
#include "Object.hpp"
#include "Shader.hpp"

#include <fstream>

//shader convention constants
//name of modelView uniform variable
const char * const modelViewUniform = "modelView";
//location of vertex position
const GLint vertPosnAttrib = 0;

//default box data
const GLfloat boxPositions[] = {
    0.75f, 0.75f, 0.0f, 1.0f,
    0.75f, -0.75f, 0.0f, 1.0f,
    -0.75f, 0.75f, 0.0f, 1.0f,
    -0.75f, -0.75f, 0.0f, 1.0f,
};

const GLint boxIndices[] = {
    0, 1, 2, 1, 2, 3
};

Object::Object()
    : program("simple.vert", "simple.frag")
{
    //use default box
    init(std::vector<GLfloat>(std::begin(boxPositions), std::end(boxPositions)),
        std::vector<GLint>(std::begin(boxIndices), std::end(boxIndices)));
}

Object::Object(const char* filename)
    : program("simple.vert", "simple.frag")
{
    std::ifstream obj(filename);
    std::vector<GLfloat> verts;
    std::vector<GLint> indices;

    if (obj.fail())
        throw "Cannot open object file";
        
    char letter;
    GLfloat x, y, z;
    GLint a, b, c;

    while(obj)
    {
        obj >> letter;
        if (letter == 'v')
        {
            obj >> x >> y >> z;
            verts.push_back(x);
            verts.push_back(y);
            verts.push_back(z);
            verts.push_back(1.);
        }
        else if (letter == 'f')
        {
            obj >> a >> b >> c;
            //whose brilliant idea was it to make this 1-based
            indices.push_back(a - 1);
            indices.push_back(b - 1);
            indices.push_back(c - 1);
        }
    }

    init(verts, indices);
}

void Object::init(const std::vector<GLfloat>& verts, const std::vector<GLint>& indices)
{
    //create a vertex array object for the object and bind it as current.
    //this holds most of the rendering state of the object.
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    //generate a new buffer object for positionBufferObject
    glGenBuffers(1, &positionBufferObject);

    //bind the newly-created buffer object positionBufferObject as the current GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
    //upload the data in vertexPositions to the current GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, verts.size()*sizeof(GLfloat), verts.data(), GL_STATIC_DRAW);

    //enable generic attribute array vertPosnArray (0) in the current vertex array object (VAO)
    //this is referenced in the vertex shader as "layout(location = 0) in vec4 position;"
    glEnableVertexAttribArray(vertPosnAttrib);

    //associate the buffer data bound to GL_ARRAY_BUFFER with the attribute in index 0
    //the final argument to this call is an integer offset, cast to pointer type. don't ask me why.
    glVertexAttribPointer(vertPosnAttrib, 4, GL_FLOAT, GL_FALSE, 0, static_cast<GLvoid*>(0));

    //clear the currently bound GL_ARRAY_BUFFER; it has been associated with the VAO by
    //glVertexAttribPointer and GL will remember it
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    //generate a new buffer object for the vertex indices
    glGenBuffers(1, &indexBufferObject);

    //GL_ELEMENT_ARRAY_BUFFER binding is part of the current VAO state, therefore we do not unbind it
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        indices.size()*sizeof(GLint), indices.data(),  GL_STATIC_DRAW);

    //remember how many vertecies we have
    numVertecies = indices.size();
}

Object::~Object()
{
    //delete VAO and buffers
    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &positionBufferObject);
    glDeleteBuffers(1, &indexBufferObject);
}

void Object::draw(const glm::mat4& transform)
{
    //make the objects VAO current. this brings in all the associated data.
    glBindVertexArray(vertexArrayObject);

    //set our shader current
    program.use();

    //find the uniform variable called modelView
    GLint mvUnif = program.GetUniformLocation(modelViewUniform);

    //set it to the matrix
    glUniformMatrix4fv(mvUnif, 1, GL_FALSE, glm::value_ptr(transform));

    //draw verteces according to the index and position buffer objects
    //the final argument to this call is an integer offset, cast to pointer type. don't ask me why.
    glDrawElements(GL_TRIANGLES, numVertecies, GL_UNSIGNED_INT, static_cast<GLvoid*>(0));
}