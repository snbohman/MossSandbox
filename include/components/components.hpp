#pragma once

#include <includes.hpp>


struct Transform {
    glm::f32vec2 position;
    glm::f32vec2 size;
};

struct Physics {
    glm::f32vec2 velocity;
    glm::f32 acceleration;
};

struct Material {
    glm::f32vec4 color;
};
