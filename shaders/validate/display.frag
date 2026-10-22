#version 450
layout(location = 0) in vec2 uv;
layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D fieldA;
layout(binding = 1) uniform sampler2D fieldB;
layout(std430, binding = 2) readonly buffer CounterBuf { uint c[]; } counter;

layout(push_constant) uniform Push { float time; float width; float height; float frame; } pc;

bool inside(vec2 t) {
    return all(greaterThanEqual(t, vec2(0.0))) && all(lessThanEqual(t, vec2(1.0)));
}

vec3 tone(vec3 c) {
    return 1.0 - exp(-2.0 * max(c, vec3(0.0)));
}

void main() {
    vec2 size = vec2(0.30, 0.45);
    vec2 ta = (uv - vec2(0.04, 0.50)) / size;
    vec2 tb = (uv - vec2(0.36, 0.50)) / size;
    vec2 tc = (uv - vec2(0.68, 0.50)) / size;

    vec4 result = vec4(0.0);
    if (inside(ta)) {
        result = vec4(tone(textureLod(fieldA, ta, 0.0).rgb), 1.0);
    } else if (inside(tb)) {
        result = vec4(tone(textureLod(fieldB, tb, 0.0).rgb), 1.0);
    } else if (inside(tc)) {
        // 3 increments per frame, starting from zero on frame 0
        uint want = uint(pc.frame) * 3u + 3u;
        bool ok = counter.c[0] == want && counter.c[63] == want;
        float bits = float(counter.c[0] & 255u) / 255.0;
        vec3 color = ok ? vec3(0.1, 0.7, 0.2) : vec3(0.8, 0.1, 0.1);
        color *= 0.6 + 0.4 * step(tc.x, bits);
        result = vec4(color, 1.0);
    }
    outColor = result;
}
