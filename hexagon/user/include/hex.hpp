#pragma once

#include <moss/includes.hpp>
#include <moss/ecs/systems.hpp>


namespace hexagon {

class HexSystem : public moss::System {
public:
    void tick(moss::SystemTickCrate crate) override;
};

}; // hexagon
