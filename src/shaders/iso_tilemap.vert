#version 330 core

layout (location = 0) in vec4 vertexPos;
layout (location = 1) in vec2 mapCoord;

uniform mat4 isoMatrix;
uniform mat4 modelMatrix;
uniform mat4 cameraMatrix;
uniform mat4 projectionMatrix;

uniform vec2 mapSize;
uniform vec2 tilePixelSize;

out vec2 vMapCoord;

void main(void) {
    gl_Position =
        projectionMatrix *
        cameraMatrix *
        modelMatrix *
        isoMatrix * 
        vertexPos;

    vMapCoord = mapCoord;
}

