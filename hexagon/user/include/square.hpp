#pragma once

#include <moss/includes.hpp>
#include <moss/ecs/systems.hpp>


namespace hexagon {

class SquareSystem : public moss::System {
public:
    void tick(moss::SystemTickCrate crate) override;
};

}; // hexagon
