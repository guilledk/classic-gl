#version 330 core

in vec4 vertexPos;

uniform mat4 modelMatrix;
uniform mat4 cameraMatrix;
uniform mat4 projectionMatrix;

void main() {
    gl_Position = projectionMatrix * cameraMatrix * modelMatrix * vertexPos;
}

