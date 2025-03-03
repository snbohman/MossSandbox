#pragma once

#include <moss/includes.hpp>
#include <moss/ecs/systems.hpp>


namespace hexagon {

class BallSystem : public moss::System {
public:
    void tick(entt::registry& registry) override;
};

}; // hexagon
