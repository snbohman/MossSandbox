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
    raylib::SetTraceLogLevel(raylib::LOG_WARNING);
    raylib::InitWindow(
        gameConfig["core"]["windowDimensions"][0].get<glm::u16>(),
        gameConfig["core"]["windowDimensions"][1].get<glm::u16>(),
        gameConfig["core"]["title"].get<std::string>().c_str()
    );
    raylib::SetTargetFPS(gameConfig["core"]["targetFPS"].get<glm::u16>());
}

void initEntt(const json& gameConfig, entt::registry& registry) {
    entt::entity ball = registry.create();

    // Ball
    registry.emplace<BallTag>(ball);
    registry.emplace<CircleTransform>(ball, utils::jsonToVec2<glm::f32vec2>(gameConfig["ball"]["position"]), gameConfig["ball"]["radius"].get<glm::f32>());
    registry.emplace<Physics>(ball, utils::jsonToVec2<glm::f32vec2>(gameConfig["ball"]["velocity"]), gameConfig["ball"]["acceleration"].get<glm::f32>());
    registry.emplace<Material>(ball, utils::jsonToVec4<glm::f32vec4>(gameConfig["ball"]["color"]));

    // Hexagon
}
