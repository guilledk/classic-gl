#version 330 core

in vec2 vTexCoord;
uniform sampler2D texSampler;

out vec4 fragColor;

void main() {
    fragColor = texture(texSampler, vTexCoord);
}

