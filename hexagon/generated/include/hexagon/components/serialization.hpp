#pragma once

#include <moss/includes.hpp>
#include <moss/components/serialization.hpp>
#include <hexagon/components/components.hpp>

namespace hexagon {
    SERIALIZE_COMPONENT(hexagon::RotationDevice, rotationSpeed, clockWise);
}
