#include <moss/ecs/components.hpp>
#include <hexagon/ecs/components.hpp>
#include <moss/ecs/systems.hpp>
#include <hex.hpp>


void hexagon::HexSystem::tick(moss::SystemTickCrate crate) {
    moss::RegPolyTransform& transform = crate.registry.get<moss::RegPolyTransform>(crate.entity);
    hexagon::RotationDevice& device = crate.registry.get<hexagon::RotationDevice>(crate.entity);

    transform.rotation += device.rotationSpeed * (device.clockWise ? 1 : -1);
}
