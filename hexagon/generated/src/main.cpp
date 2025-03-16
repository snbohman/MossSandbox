#include <moss/defines.hpp>
#include <moss/core/app.hpp>
#include <hexagon/ecs/serialization.hpp>
#include <hexagon/ecs/components.hpp>
#include <ball.hpp>
#include <hex.hpp>
#include <square.hpp>


int main() {
    /* -- App -- */
    spdlog::set_level(spdlog::level::debug);
    moss::App app;

    /* -- Registration -- */
    moss::types::ComponentRegistry componentRegistry;
    app.buildComponentRegistry(componentRegistry);
    REGISTER_COMPONENT(hexagon::RotationDevice);
    REGISTER_TAG(hexagon::BallTag);
    REGISTER_TAG(hexagon::HexTag);
    REGISTER_TAG(hexagon::SquareTag);
    REGISTER_SYSTEM(hexagon::BallSystem, {});
    REGISTER_SYSTEM(hexagon::HexSystem, {});
    REGISTER_SYSTEM(hexagon::SquareSystem, {});
    app.setComponentRegistry(componentRegistry);

    /* -- Scenes -- */
    app.addScene("scene1", true);

    /* -- Run -- */
    app.run();
}
