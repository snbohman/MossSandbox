#pragma once

#include <moss/includes.hpp>
#include <moss/ecs/serialization.hpp>
#include <hexagon/ecs/componentDefinitions.hpp>
#include <moss/ecs/systems.hpp>

namespace hexagon {
    SERIALIZE_COMPONENT(hexagon::RotationDevice, rotationSpeed, clockWise);
}
