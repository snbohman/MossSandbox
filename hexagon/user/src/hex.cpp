#include <moss/ecs/components.hpp>
#include <hexagon/ecs/components.hpp>
#include <hex.hpp>


void hexagon::HexSystem::tick(entt::registry& registry) {
    entt::entity hexagon = *registry.view<hexagon::HexTag>().begin();
    moss::RegPolyTransform& transform = registry.get<moss::RegPolyTransform>(hexagon);
    hexagon::RotationDevice& device = registry.get<hexagon::RotationDevice>(hexagon);

    transform.rotation += device.rotationSpeed * (device.clockWise ? 1 : -1);
}
