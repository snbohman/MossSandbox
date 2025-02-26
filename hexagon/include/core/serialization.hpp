#pragma once

#include <moss/includes.hpp>
#include <moss/components/serialization.hpp>
#include <components/tags.hpp>
#include <hex/components.hpp>

namespace hexagon {
    SERIALIZE_COMPONENT(hexagon::RotationDevice, rotationSpeed, clockWise);
}
