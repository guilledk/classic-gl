#version 330 core

in vec2 vTexCoord;
uniform sampler2D texSampler;
uniform vec4 color;

out vec4 fragColor;

vec4 grayscale(in vec4 v) {
  float average = (v.r + v.g + v.b) / 3.0;
  return vec4(average, average, average, v.a);
}

vec4 colorize(in vec4 grayscale, in vec4 c) {
    return (grayscale * c);
}

void main(void) {
    vec4 texColor = texture(texSampler, vTexCoord);
    vec4 grayScaleColor = grayscale(texColor);
    fragColor = colorize(grayScaleColor, color);
}

