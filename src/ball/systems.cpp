#include <includes.hpp>
#include <core/state.hpp>
#include <ball/systems.hpp>
#include <components/components.hpp>
#include <components/tags.hpp>
#include <utils.hpp>


void Ball::update(entt::registry& registry) {
    entt::entity ball = *registry.view<BallTag>().begin();
    CircleTransform& ballTransform = registry.get<CircleTransform>(ball);
    Physics& ballPhysics = registry.get<Physics>(ball);

    entt::entity hex = *registry.view<HexTag>().begin();
    RegPolyTransform& hexTransform = registry.get<RegPolyTransform>(hex);

    glm::f32vec2 normal;
    if (Ball::collide(ballTransform, hexTransform, normal)) {
        glm::f32 dot = glm::dot(ballPhysics.velocity, normal);
        glm::f32vec2 reflection = ballPhysics.velocity - 2.0f * dot * normal;
        
        ballPhysics.velocity = reflection;
        ballTransform.position += ballPhysics.velocity * raylib::GetFrameTime();
    } else {
        ballPhysics.velocity += ballPhysics.acceleration * raylib::GetFrameTime();
        ballTransform.position += ballPhysics.velocity * raylib::GetFrameTime();
    }

}

bool Ball::collide(const CircleTransform& ball, const RegPolyTransform& hex, glm::f32vec2& normal) {
    std::vector<glm::f32vec2> vertices; vertices.reserve(hex.numPoints);
    for (int i = 0; i < hex.numPoints; i++) {
        glm::f32 theta = glm::radians(hex.rotation) + i * M_PI / 3 + M_PI / 6;
        vertices.push_back({
            hex.position.x + hex.radius * glm::sin(-theta),
            hex.position.y + hex.radius * glm::cos(-theta)
        });
    }

    for (int i = 0; i < hex.numPoints; i++) {
        glm::f32vec2 start = vertices[i];
        glm::f32vec2 end = vertices[(i + 1) % 6]; // Wrap to first with mod
        glm::f32 distance = utils::math::distancePointToLine(ball.position, start, end);
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
