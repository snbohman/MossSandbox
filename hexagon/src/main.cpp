#include <moss/includes.hpp>
#include <moss/core/init.hpp>
#include <moss/render/systems.hpp>
#include <components/serialization.hpp>
#include <components/tags.hpp>
#include <hex/components.hpp>
#include <hex/systems.hpp>
#include <ball/systems.hpp>
#include <fstream>


int main() {
    entt::registry registry;
    const json& gameConfig = json::parse(std::ifstream("hexagon/data/gameConfig.json"));
    moss::initRaylib(gameConfig);

    moss::ComponentRegistry componentRegistry; moss::buildComponentRegistry(registry, componentRegistry);
    moss::registerComponent<hexagon::RotationDevice>(registry, componentRegistry, "hexagon::RotationDevice");
    moss::registerTag<hexagon::BallTag>(registry, componentRegistry, "hexagon::BallTag");
    moss::registerTag<hexagon::HexTag>(registry, componentRegistry, "hexagon::HexTag");
    moss::initEntt(gameConfig, registry, componentRegistry);

    while (!raylib::WindowShouldClose()) {
        hexagon::hex::update(registry);
        hexagon::ball::update(registry);
        moss::render::update(registry);
    }

    raylib::CloseWindow();
}
