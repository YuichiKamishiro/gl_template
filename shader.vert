#version 460

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 color;

out vec3 colors;

void main() {
    colors = color;
    gl_Position = vec4(position.x, position.y, 1, 1);
}
