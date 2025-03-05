#include <moss/includes.hpp>
#include <moss/ecs/systems.hpp>
#include <hexagon/ecs/components.hpp>
#include <square.hpp>

void hexagon::SquareSystem::tick(moss::SystemTickCrate crate) {
    moss::RectTransform& transform = crate.registry.get<moss::RectTransform>(crate.entity);
    hexagon::RotationDevice& device = crate.registry.get<hexagon::RotationDevice>(crate.entity);
    transform.rotation += device.rotationSpeed * (device.clockWise ? 1 : -1);
}
