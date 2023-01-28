#version 460 compatibility

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec3 colors;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main() {
    colors = color;
    gl_Position = Projection * View * Model * vec4(position, 1);
}
