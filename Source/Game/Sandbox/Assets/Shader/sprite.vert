#version 330 core

layout (location = 0) vec3 POSITION;

uniform mat4 modelMVP;

void main() {
    gl_Position = modelMVP * vec4(POSITION, 1.0);
}
