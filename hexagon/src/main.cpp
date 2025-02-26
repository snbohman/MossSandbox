#include <moss/includes.hpp>
#include <moss/core/init.hpp>
#include <moss/render/systems.hpp>
#include <core/serialization.hpp>
#include <components/tags.hpp>
#include <hex/components.hpp>
#include <hex/systems.hpp>
#include <ball/systems.hpp>
#include <fstream>


int main() {
    entt::registry registry;
    const json& gameConfig = json::parse(std::ifstream("hexagon/data/gameConfig.json"));
    moss::initRaylib(gameConfig);

    moss::ComponentMap componentMap; moss::buildComponentMap(registry, componentMap);
    MAP_COMPONENT(componentMap, hexagon::RotationDevice);
    MAP_TAG(componentMap, hexagon::BallTag);
    MAP_TAG(componentMap, hexagon::HexTag);

    moss::initEntt(gameConfig, registry, componentMap);

    while (!raylib::WindowShouldClose()) {
        hexagon::hex::update(registry);
        hexagon::ball::update(registry);
        moss::render::update(registry);
    }

    raylib::CloseWindow();
}
