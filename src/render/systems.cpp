#include <includes.hpp>
#include <render/systems.hpp>
#include <components/components.hpp>


void Render::update(entt::registry& registry) {
    raylib::ClearBackground(raylib::BLACK);
    raylib::BeginDrawing();
    
    for (auto entity : registry.view<RectTransform>()) {
        RectTransform& transform = registry.get<RectTransform>(entity);
        Material& material = registry.get<Material>(entity);
        raylib::DrawRectangle(
            transform.position.x, transform.position.y,
            transform.size.x, transform.size.y,
            raylib::ColorFromNormalized( { material.color.r, material.color.g, material.color.b, material.color.a } )
        );
    }

    for (auto entity : registry.view<CircleTransform>()) {
        CircleTransform& transform = registry.get<CircleTransform>(entity);
        Material& material = registry.get<Material>(entity);
        raylib::DrawCircle(
            transform.position.x, transform.position.y,
            transform.radius,
            raylib::ColorFromNormalized( { material.color.r, material.color.g, material.color.b, material.color.a } )
        );
    }

    raylib::EndDrawing();
}
