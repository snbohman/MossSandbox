#include <includes.hpp>
#include <core/init.hpp>
#include <ball/systems.hpp>
#include <render/systems.hpp>

int main() {
    entt::registry registry;
    init(registry);

    while (!raylib::WindowShouldClose()) {
        Ball::update(registry);
        Render::update(registry);
    }

    raylib::CloseWindow();
}
