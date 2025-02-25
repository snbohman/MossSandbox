#include <includes.hpp>
#include <core/state.hpp>
#include <player/systems.hpp>
#include <components/components.hpp>
#include <components/tags.hpp>


void Player::update(entt::registry& registry) {
    entt::entity player = *registry.view<PlayerTag>().begin(); // Take the first entt, as only one exist
    Transform& transform = registry.get<Transform>(player);
    Physics& physics = registry.get<Physics>(player);

    if (raylib::IsKeyDown(raylib::KEY_A)) physics.velocity.x -= 1;
    if (raylib::IsKeyDown(raylib::KEY_D)) physics.velocity.x += 1;
    if (raylib::IsKeyDown(raylib::KEY_S)) physics.velocity.y += 1;
    if (raylib::IsKeyDown(raylib::KEY_W)) physics.velocity.y -= 1;

    if (glm::length(physics.velocity) == 0) return;
    transform.position += physics.acceleration * glm::normalize(physics.velocity);
    physics.velocity = {0, 0};
}
