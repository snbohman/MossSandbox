#pragma once

#include <includes.hpp>
#include <components/components.hpp>


namespace Ball {

void update(entt::registry& registry);
bool collide(const CircleTransform& ball, const RegPolyTransform& hex, glm::f32vec2& hitLine);

}
