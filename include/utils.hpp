#pragma once

#include <includes.hpp>


namespace utils {

template<typename V>
inline V jsonToVec2(const json& j) {
    return V(
        j[0].get<float>(),
        j[1].get<float>()
    );
}

template<typename V>
inline V jsonToVec3(const json& j) {
    return V(
        j[0].get<float>(),
        j[1].get<float>(),
        j[2].get<float>()
    );
}

template<typename V>
inline V jsonToVec4(const json& j) {
    return V(
        j[0].get<float>(),
        j[1].get<float>(),
        j[2].get<float>(),
        j[3].get<float>()
    );
}

}
