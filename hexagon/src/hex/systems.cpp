#include <moss/components/components.hpp>
#include <components/tags.hpp>
#include <hex/systems.hpp>
#include <hex/components.hpp>


void hexagon::hex::update(entt::registry& registry) {
    entt::entity hexagon = *registry.view<hexagon::HexTag>().begin();
    moss::RegPolyTransform& transform = registry.get<moss::RegPolyTransform>(hexagon);
    RotationDevice& device = registry.get<hexagon::RotationDevice>(hexagon);

    transform.rotation += device.rotationSpeed * (device.clockWise ? 1 : -1);
}
