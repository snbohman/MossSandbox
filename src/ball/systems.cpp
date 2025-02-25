#include <includes.hpp>
#include <core/state.hpp>
#include <ball/systems.hpp>
#include <components/components.hpp>
#include <components/tags.hpp>


void Ball::update(entt::registry& registry) {
    entt::entity ball = *registry.view<BallTag>().begin(); // Take the first entt, as only one exist
    CircleTransform& transform = registry.get<CircleTransform>(ball);
    Physics& physics = registry.get<Physics>(ball);

    if (raylib::IsKeyDown(raylib::KEY_A)) physics.velocity.x -= 1;
    if (raylib::IsKeyDown(raylib::KEY_D)) physics.velocity.x += 1;
    if (raylib::IsKeyDown(raylib::KEY_S)) physics.velocity.y += 1;
    if (raylib::IsKeyDown(raylib::KEY_W)) physics.velocity.y -= 1;

    if (glm::length(physics.velocity) == 0) return;
    transform.position += physics.acceleration * glm::normalize(physics.velocity);
    physics.velocity = {0, 0};
}
