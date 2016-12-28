#define RSTRING(A) #A

// SHADER_POSITION_COLOR
static const GLchar* s_vertexPositionColor = RSTRING(
\n#version 330 core\n
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
out vec4 outColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main() {
    gl_Position = projection * view * model * vec4(position, 1.0);
    outColor = color;
}
);

static const GLchar* s_fragmentPositionColor = RSTRING(
\n#version 330 core\n
out vec4 color;
in vec4 outColor;
void main() {
    color = outColor;
    if (color.a < 0.1) discard;
}
);

// SHADER_POSITION_COLOR_TEXTURE
static const GLchar* s_vertexPositionColorTexture = RSTRING(
\n#version 330 core\n
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;
out vec4 outColor;
out vec2 TexCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main() {
    gl_Position = projection * view * model * vec4(position, 1.0);
    outColor = color;
    TexCoord = texCoord;
}
);

static const GLchar* s_fragmentPositionColorTexture = RSTRING(
\n#version 330 core\n
out vec4 color;
in vec4 outColor;
in vec2 TexCoord;
uniform sampler2D texture0;
void main() {
    color = texture(texture0, TexCoord) * outColor;
    if (color.a < 0.1) discard;
}
);

// SHADER_POSITION_COLOR_NO_MVP
static const GLchar* s_vertexPositionColorNoMVP = RSTRING(
\n#version 330 core\n
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
out vec4 outColor;
void main() {
    gl_Position = vec4(position, 1.0);
    outColor = color;
}
);

static const GLchar* s_fragmentPositionColorNoMVP = RSTRING(
\n#version 330 core\n
out vec4 color;
in vec4 outColor;
void main() {
    color = outColor;
    if (color.a < 0.1) discard;
}
);

// SHADER_POSITION_COLOR_TEXTURE_NO_MVP
static const GLchar* s_vertexPositionColorTextureNoMVP = RSTRING(
\n#version 330 core\n
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;
out vec4 outColor;
out vec2 TexCoord;
void main() {
    gl_Position = vec4(position, 1.0);
    outColor = color;
    TexCoord = texCoord;
}
);

static const GLchar* s_fragmentPositionColorTextureNoMVP = RSTRING(
\n#version 330 core\n
out vec4 color;
in vec4 outColor;
in vec2 TexCoord;
uniform sampler2D texture0;
void main() {
    color = texture(texture0, TexCoord) * outColor;
    if (color.a < 0.1) discard;
}
);

