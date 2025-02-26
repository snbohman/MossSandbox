#pragma once

#include <includes.hpp>


struct RectTransform {
    glm::f32vec2 position;
    glm::f32vec2 size;
    glm::f32 rotation;
};

struct CircleTransform {
    glm::f32vec2 position;
    glm::f32 radius;
};

struct PolyTransform {
    std::vector<glm::f32vec2> points;
};

struct RegPolyTransform {
    glm::f32vec2 position;
    glm::u16 numPoints;
    glm::f32 radius;
    glm::f32 rotation;
};

struct Physics {
    glm::f32vec2 velocity;
    glm::f32vec2 acceleration;
};

struct Material {
    glm::f32vec4 color;
    glm::f32 thickness;
    bool fill;
};
