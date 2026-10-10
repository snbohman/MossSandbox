#version 450

layout(location = 0) in vec2 uv;
layout(location = 0) out vec4 outColor;

void main() {
    // Product of two sine waves gives a checker-like ripple grid, range -1..1
    float wave = sin(uv.x * 20.0) * sin(uv.y * 20.0);
    float v = 0.5 + 0.5 * wave;

    outColor = vec4(v, 0.4 * v + 0.2, 1.0 - v, 1.0);
}
