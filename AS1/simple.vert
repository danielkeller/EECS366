#version 330

layout(location = 0) in vec4 position;
void main()
{
    gl_Position = position;
    gl_Position.xyz *= .4; //make it fit on the screen
}