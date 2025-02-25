#include <includes.hpp>
#include <core/init.hpp>
#include <components/components.hpp>
#include <components/tags.hpp>
#include <utils.hpp>
#include <fstream>


void init(entt::registry& registry) {
    json gameConfig = json::parse(std::ifstream("data/gameConfig.json"));
    initRaylib(gameConfig);
    initEntt(gameConfig, registry);
}

void initRaylib(const json& gameConfig) {
    raylib::InitWindow(
        gameConfig["core"]["windowDimensions"][0].get<glm::u16>(),
        gameConfig["core"]["windowDimensions"][1].get<glm::u16>(),
        gameConfig["core"]["title"].get<std::string>().c_str()
    );
    raylib::SetTargetFPS(gameConfig["core"]["targetFPS"].get<glm::u16>());
}

void initEntt(const json& gameConfig, entt::registry& registry) {
    entt::entity player = registry.create();
    registry.emplace<PlayerTag>(player);
    registry.emplace<Transform>(player, utils::jsonToVec2<glm::f32vec2>(gameConfig["player"]["position"]), utils::jsonToVec2<glm::f32vec2>(gameConfig["player"]["size"]));
    registry.emplace<Physics>(player, utils::jsonToVec2<glm::f32vec2>(gameConfig["player"]["velocity"]), gameConfig["player"]["acceleration"].get<glm::f32>());
    registry.emplace<Material>(player, utils::jsonToVec4<glm::f32vec4>(gameConfig["player"]["color"]));
}
