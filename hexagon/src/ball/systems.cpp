#include <moss/includes.hpp>
#include <moss/components/components.hpp>
#include <moss/utils.hpp>
#include <ball/systems.hpp>
#include <components/tags.hpp>


void hexagon::ball::update(entt::registry& registry) {
    entt::entity ball = *registry.view<hexagon::BallTag>().begin();
    moss::CircleTransform& ballTransform = registry.get<moss::CircleTransform>(ball);
    moss::Physics& ballPhysics = registry.get<moss::Physics>(ball);

    entt::entity hex = *registry.view<hexagon::HexTag>().begin();
    moss::RegPolyTransform& hexTransform = registry.get<moss::RegPolyTransform>(hex);

    glm::f32vec2 normal;
    if (hexagon::ball::collide(ballTransform, hexTransform, normal)) {
        glm::f32 dot = glm::dot(ballPhysics.velocity, normal);
        glm::f32vec2 reflection = ballPhysics.velocity - 2.0f * dot * normal;
        
        ballPhysics.velocity = reflection;
        ballTransform.position += ballPhysics.velocity * raylib::GetFrameTime();
    } else {
        ballPhysics.velocity += ballPhysics.acceleration * raylib::GetFrameTime();
        ballTransform.position += ballPhysics.velocity * raylib::GetFrameTime();
    }

}

bool hexagon::ball::collide(const moss::CircleTransform& ball, const moss::RegPolyTransform& hex, glm::f32vec2& normal) {
    std::vector<glm::f32vec2> vertices; vertices.reserve(hex.numPoints);
    for (int i = 0; i < hex.numPoints; i++) {
        glm::f32 innerAngle = 2 * M_PI / hex.numPoints;
        glm::f32 theta = glm::radians(hex.rotation) + i * innerAngle + innerAngle / 2;
        vertices.push_back({
            hex.position.x + hex.radius * glm::sin(-theta),
            hex.position.y + hex.radius * glm::cos(-theta)
        });
    }

    for (int i = 0; i < hex.numPoints; i++) {
        glm::f32vec2 start = vertices[i];
        glm::f32vec2 end = vertices[(i + 1) % 6]; // Wrap to first with mod
        glm::f32 distance = moss::utils::math::distancePointToLine(ball.position, start, end);
        if (distance <= ball.radius) {
            glm::f32vec2 hitLine = start - end;

            glm::f32vec2 normalx = glm::normalize(glm::f32vec2(-hitLine.y, hitLine.x) * raylib::GetFrameTime());
            glm::f32vec2 normaly = glm::normalize(glm::f32vec2(hitLine.y, -hitLine.x) * raylib::GetFrameTime());
            if (glm::dot(normalx, hex.position - ball.position) < 0) normal = normalx;
            else normal = normaly;

            return true;
        }
    }

    return false;
}
