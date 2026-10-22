#version 450

layout(location = 0) in vec2 uv;
layout(location = 0) out vec4 outColor;

// Must match GradientParams in gradient.cpp (6 floats, 24 bytes), same order
layout(push_constant) uniform Push {
    float time;
    float mousex;
    float mousey;
    float width;
    float height;
    float pad;
} pc;

void main() {
    // Cosine palette: a smooth rainbow drifting across the screen over time
    vec3 phase = vec3(0.0, 2.0, 4.0);
    vec3 color = 0.5 + 0.5 * cos(pc.time + uv.x * pc.mousex / pc.width + uv.y * pc.mousey / pc.height + phase);
    outColor = vec4(color, 1.0);
}
