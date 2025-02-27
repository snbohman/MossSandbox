#pragma once

#include <moss/includes.hpp>
#include <moss/components/components.hpp>


namespace hexagon {
namespace ball {

void update(entt::registry& registry);
bool collide(const moss::CircleTransform& ball, const moss::RegPolyTransform& hex, glm::f32vec2& normal1);

} // ball
} // hexagon
