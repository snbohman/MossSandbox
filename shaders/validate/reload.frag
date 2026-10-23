#version 450

layout(location = 0) in vec2 uv;
layout(location = 0) out vec4 outColor;

// Must match Params in validate.cpp (4 floats, 16 bytes), same order
layout(push_constant) uniform Push {
    float time;
    float width;
    float height;
    float frame;
} pc;

void main() {
    // A 96x96 px swatch, 16 px from the top-right corner
    vec2 px = uv * vec2(pc.width, pc.height);
    vec2 fromCorner = vec2(pc.width - px.x, px.y) - vec2(16.0);
    bool inside = all(greaterThanEqual(fromCorner, vec2(0.0)))
               && all(lessThan(fromCorner, vec2(96.0)));

    // RELOAD TEST: change this colour, recompile, and the swatch changes.
    // The pulse proves the push constants still arrive after a reload.
    vec3 color = vec3(0.0, 0.5, 0.5) * (0.75 + 0.25 * sin(pc.time * 3.0));
    outColor = vec4(color, inside ? 1.0 : 0.0);
}
