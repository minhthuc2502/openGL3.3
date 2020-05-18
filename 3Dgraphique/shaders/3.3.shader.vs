#version 330 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
out vec4 vertexColor;
out vec2 TexCoord;
void main()
{
    gl_Position = aPos;
    vertexColor = aColor; 
    TexCoord = aTexCoord;
}

