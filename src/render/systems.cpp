#include <includes.hpp>
#include <render/systems.hpp>
#include <components/components.hpp>
#include <utils.hpp>


void Render::update(entt::registry& registry) {
    raylib::ClearBackground(raylib::BLACK);
    raylib::BeginDrawing();
    
    for (auto entity : registry.view<RectTransform>()) {
        RectTransform& transform = registry.get<RectTransform>(entity);
        Material& material = registry.get<Material>(entity);
        raylib::DrawRectangleV(
            utils::glmToRaylib<glm::vec2, raylib::Vector2>(transform.position),
            utils::glmToRaylib<glm::vec2, raylib::Vector2>(transform.size),
            raylib::ColorFromNormalized(utils::glmToRaylib<glm::vec4, raylib::Vector4>(material.color))
        );
    }

    for (auto entity : registry.view<CircleTransform>()) {
        CircleTransform& transform = registry.get<CircleTransform>(entity);
        Material& material = registry.get<Material>(entity);
        raylib::DrawCircleV(
            utils::glmToRaylib<glm::vec2, raylib::Vector2>(transform.position),
            transform.radius,
            raylib::ColorFromNormalized(utils::glmToRaylib<glm::vec4, raylib::Vector4>(material.color))
        );
    }

    for (auto entity : registry.view<PolyTransform>()) {
        PolyTransform& transform = registry.get<PolyTransform>(entity);
        Material& material = registry.get<Material>(entity);
        raylib::DrawTriangleFan(
            utils::pointsToRaylib<glm::vec2, raylib::Vector2>(transform.points).data(),
            transform.points.size(),
            raylib::ColorFromNormalized(utils::glmToRaylib<glm::vec4, raylib::Vector4>(material.color))
        );
    }

    for (auto entity : registry.view<RegPolyTransform>()) {
        RegPolyTransform& transform = registry.get<RegPolyTransform>(entity);
        Material& material = registry.get<Material>(entity);
        if (material.fill) {
            raylib::DrawPoly(
                utils::glmToRaylib<glm::vec2, raylib::Vector2>(transform.position),
                transform.numPoints, transform.radius, transform.rotation,
                raylib::ColorFromNormalized( { material.color.r, material.color.g, material.color.b, material.color.a } )
            );
        } else {
            raylib::DrawPolyLinesEx(
                utils::glmToRaylib<glm::vec2, raylib::Vector2>(transform.position),
                transform.numPoints, transform.radius, transform.rotation, material.thickness,
                raylib::ColorFromNormalized( { material.color.r, material.color.g, material.color.b, material.color.a } )
            );
        }
    }

    raylib::EndDrawing();
}
