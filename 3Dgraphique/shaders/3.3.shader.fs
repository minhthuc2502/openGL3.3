#version 330 core
out vec4 FragColor;

in vec4 vertexColor;
in vec2 TexCoord;

uniform sampler2D Texture1;
uniform sampler2D Texture2;
uniform sampler2D texture_diffuse1;
void main()
{
    FragColor = texture(texture_diffuse1, TexCoord);
}