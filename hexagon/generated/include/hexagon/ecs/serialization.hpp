#pragma once

#include <moss/includes.hpp>
#include <moss/ecs/serialization.hpp>
#include <hexagon/ecs/componentDefinitions.hpp>

namespace hexagon {
    SERIALIZE_COMPONENT(hexagon::RotationDevice, rotationSpeed, clockWise);
}
