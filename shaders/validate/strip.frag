#version 450
layout(location = 0) in vec2 uv;
layout(location = 0) out vec4 outColor;

layout(push_constant) uniform Push { float time; float width; float height; float frame; } pc;

void main() {
    float band = 1.0 - step(0.12, uv.y);
    vec3 color = 0.5 + 0.5 * cos(pc.time + uv.x * 6.0 + vec3(0.0, 2.0, 4.0));
    outColor = vec4(color, band);
}
