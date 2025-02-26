#pragma once

#include <includes.hpp>
#include <components/components.hpp>
#include <hex/components.hpp>


template<typename T>
void loadComponent(const json& j, T& component);

template<>
void loadComponent<RectTransform>(const json& j, RectTransform& component);

template<>
void loadComponent<CircleTransform>(const json& j, CircleTransform& component);

template<>
void loadComponent<PolyTransform>(const json& j, PolyTransform& component);

template<>
void loadComponent<RegPolyTransform>(const json& j, RegPolyTransform& component);

template<>
void loadComponent<Physics>(const json& j, Physics& component);

template<>
void loadComponent<Material>(const json& j, Material& component);

template<>
void loadComponent<RotationDevice>(const json& j, RotationDevice& component);
