#include <moss/includes.hpp>
#include <moss/utils.hpp>
#include <moss/ecs/components.hpp>
#include <hexagon/ecs/components.hpp>
#include <ball.hpp>

bool collide(const moss::CircleTransform& ball, const moss::RegPolyTransform& hex, glm::f32vec2& normal) {
    std::vector<glm::f32vec2> vertices; vertices.reserve(hex.numPoints);
    for (int i = 0; i < hex.numPoints; i++) {
        glm::f32 innerAngle = 2 * M_PI / hex.numPoints;
        glm::f32 theta = glm::radians(hex.rotation) + i * innerAngle + innerAngle / 2;
        vertices.push_back({
            hex.position.x + hex.radius * glm::sin(-theta),
            hex.position.y + hex.radius * glm::cos(-theta)
        });
    }

    glm::f32 d = ball.radius + 1;
    for (int i = 0; i < hex.numPoints; i++) {
        glm::f32vec2 start = vertices[i];
        glm::f32vec2 end = vertices[(i + 1) % hex.numPoints]; // Wrap from last to first with mod
        glm::f32 distance = moss::utils::math::distancePointToLine(ball.position, start, end);
        if (distance <= ball.radius && distance < d) {
            d = distance;
            glm::f32vec2 hitLine = start - end;

            // Choosing the normal that points inwards
            glm::f32vec2 normalx = glm::normalize(glm::f32vec2(-hitLine.y, hitLine.x) * raylib::GetFrameTime());
            glm::f32vec2 normaly = glm::normalize(glm::f32vec2(hitLine.y, -hitLine.x) * raylib::GetFrameTime());
            normal = glm::dot(normalx, hex.position - ball.position) < 0 ? normalx : normaly;
        }
    }

    return normal != glm::f32vec2(0, 0);
}

void hexagon::BallSystem::tick(moss::SystemTickCrate crate) {
    moss::CircleTransform& ballTransform = crate.registry.get<moss::CircleTransform>(crate.entity);
    moss::Physics& ballPhysics = crate.registry.get<moss::Physics>(crate.entity);

    entt::entity hex = *crate.registry.view<hexagon::HexTag>().begin();
    moss::RegPolyTransform& hexTransform = crate.registry.get<moss::RegPolyTransform>(hex);

    glm::f32vec2 normal = {0, 0};
    if (collide(ballTransform, hexTransform, normal)) {
        glm::f32 dot = glm::dot(ballPhysics.velocity, normal);
        glm::f32vec2 reflection = ballPhysics.velocity - 2.0f * dot * normal;
        
        ballPhysics.velocity = reflection * ballPhysics.elasticity;
        ballTransform.position += ballPhysics.velocity * raylib::GetFrameTime();
    } else {
        ballPhysics.velocity += ballPhysics.acceleration * raylib::GetFrameTime();
        ballTransform.position += ballPhysics.velocity * raylib::GetFrameTime();
    }
}
