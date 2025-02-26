#include <components/loadComponents.hpp>
#include <hex/components.hpp>
#include <utils.hpp>



//--------------------------------------//
//---------------- Core ----------------//
//--------------------------------------//
template<typename T>
void loadComponent(const json& j, T& component) { }

template<>
void loadComponent<RectTransform>(const json& j, RectTransform& component) {
    component.position = utils::jsonToVec<glm::f32vec2>(j["position"]);
    component.size = utils::jsonToVec<glm::f32vec2>(j["size"]);
}

template<>
void loadComponent<CircleTransform>(const json& j, CircleTransform& component) {
    component.position = utils::jsonToVec<glm::f32vec2>(j["position"]);
    component.radius = j["radius"].get<glm::f32>();
}

template<>
void loadComponent<PolyTransform>(const json& j, PolyTransform& component) {
    component.points = utils::jsonToPoints<glm::f32vec2>(j["points"]);
}

template<>
void loadComponent<RegPolyTransform>(const json& j, RegPolyTransform& component) {
    component.position = utils::jsonToVec<glm::f32vec2>(j["position"]);
    component.numPoints = j["numPoints"].get<glm::u8>();
    component.radius = j["radius"].get<glm::f32>();
    component.rotation = j["rotation"].get<glm::f32>();
}

template<>
void loadComponent<Physics>(const json& j, Physics& component) {
    component.velocity = utils::jsonToVec<glm::f32vec2>(j["velocity"]);
    component.acceleration = utils::jsonToVec<glm::f32vec2>(j["acceleration"]);
}

template<>
void loadComponent<Material>(const json& j, Material& component) {
    component.color = utils::jsonToVec<glm::f32vec4>(j["color"]);
    component.fill = j["fill"].get<bool>();
    component.thickness = j["thickness"].get<glm::f32>();
}

//--------------------------------------------------//
//---------------- Hexagon Specific ----------------//
//--------------------------------------------------//
template<>
void loadComponent<RotationDevice>(const json& j, RotationDevice& component) {
    component.rotationSpeed = j["color"].get<glm::f32>();
    component.clockWise = j["fill"].get<bool>();
}
