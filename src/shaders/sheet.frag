#version 330 core

in vec2 vTexCoord;
out vec4 fragColor;

uniform sampler2D texSampler;
uniform vec2 tileSetSize;
uniform float tileIdFlat;

vec4 getTilePixel(float tileIdFlat, vec2 texCoord) {
    vec2 tileId = vec2(
        floor(mod(tileIdFlat, tileSetSize.x)),
        floor(tileIdFlat / tileSetSize.x));

    vec2 setNormalSize = vec2(1, 1) / tileSetSize;
    vec2 tileCornerNorm = tileId * setNormalSize;
    vec2 localTileCoord = texCoord * setNormalSize;

    return texture(texSampler, tileCornerNorm + localTileCoord);
}

void main(void) {
    fragColor = getTilePixel(tileIdFlat, vec2(vTexCoord.x, vTexCoord.y));
}

