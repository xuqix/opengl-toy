
#version 330 core
out vec4 color;
in vec4 ourColor;
in vec2 TexCoord;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
void main()
{
    color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.2);
}
