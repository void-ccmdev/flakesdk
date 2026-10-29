#version 330

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aColor;

out vec4 vertexColor;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(aPosition, 1.0);
    vertexColor = vec4(aColor, 1.0f);
}