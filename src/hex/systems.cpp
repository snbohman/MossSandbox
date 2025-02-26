#include <hex/systems.hpp>
#include <hex/components.hpp>
#include <components/components.hpp>
#include <components/tags.hpp>


void Hex::update(entt::registry& registry) {
    entt::entity hexagon = *registry.view<HexTag>().begin();
    RegPolyTransform& transform = registry.get<RegPolyTransform>(hexagon);
    RotationDevice& device = registry.get<RotationDevice>(hexagon);

    transform.rotation += device.rotationSpeed * (device.clockWise ? 1 : -1);
}
