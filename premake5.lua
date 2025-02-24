workspace "softbody"
    configurations { "debug", "release" }
    architecture "x86_64"

project "softbody"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "build/%{cfg.buildcfg}"

    files { "src/**.cpp", "src/core/**.cpp", "src/render/**.cpp", "src/player/**.cpp" }
    includedirs { "include", "entt", "raylib", "fmt" }
    links { "raylib", "fmt" }

    filter "configurations:debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:release"
        defines { "NDEBUG" }
        optimize "On"
