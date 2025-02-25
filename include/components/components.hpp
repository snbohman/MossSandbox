#pragma once

#include <includes.hpp>


struct RectTransform {
    glm::f32vec2 position;
    glm::f32vec2 size;
};

struct CircleTransform {
    glm::f32vec2 position;
    glm::f32 radius;
};

struct LineTransform {
    glm::f32vec2 p1;
    glm::f32vec2 p2;
    glm::f32 thickness;
};

struct PolyTransform {
    std::vector<glm::f32vec2> points;
    glm::f32 thickness;
    bool fill;
};

struct Physics {
    glm::f32vec2 velocity;
    glm::f32 acceleration;
};

struct Material {
    glm::f32vec4 color;
};
