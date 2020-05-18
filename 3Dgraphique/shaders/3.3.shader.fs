#version 330 core
out vec4 FragColor;

in vec4 vertexColor;
in vec2 TexCoord;

uniform sampler2D Texture1;
uniform sampler2D Texture2;

void main()
{
    FragColor = mix(texture(Texture1, TexCoord), texture(Texture2, TexCoord), 0.2);
}