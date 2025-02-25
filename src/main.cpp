#include <includes.hpp>
#include <core/init.hpp>
#include <player/systems.hpp>
#include <render/systems.hpp>

int main() {
    entt::registry registry;
    init(registry);

    while (!raylib::WindowShouldClose()) {
        Player::update(registry);
        Render::update(registry);
    }

    raylib::CloseWindow();
}
