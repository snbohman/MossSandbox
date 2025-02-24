workspace "softbody"
    configurations { "Debug", "Release" }
    architecture "x86_64"

project "softbody"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"

    files { "src/**.cpp" }
    includedirs { "include", "entt" }
    links { "raylib", "spdlog" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
